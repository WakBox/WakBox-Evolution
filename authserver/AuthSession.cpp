#include "AuthSession.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Cryptography/CryptographyMgr.h"
#include "Proto/account.pb.h"

AuthHandlerMap  AuthTable::authHandlers;

void AuthTable::InitHandlers()
{
    #define ADD_OPCODE_HANDLER(opcode, status, handler) \
        AddOpcodeHandler(opcode, #opcode, status, handler);

    ADD_OPCODE_HANDLER(CMSG_CLIENT_DISCONNECT,         STATUS_ALWAYS,   &AuthSession::HandleClientDisconnect);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,            STATUS_ALWAYS,   &AuthSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_AUTH,               STATUS_ALWAYS,   &AuthSession::HandleClientAuthentication);
    ADD_OPCODE_HANDLER(CMSG_PUBLIC_KEY_REQUEST,        STATUS_ALWAYS,   &AuthSession::HandlePublicKeyRequest);
    ADD_OPCODE_HANDLER(CMSG_REALMS_REQUEST,            STATUS_AUTHED,   &AuthSession::HandleRealmsRequest);
    ADD_OPCODE_HANDLER(CMSG_AUTH_TOKEN_REQUEST,        STATUS_AUTHED,   &AuthSession::HandleAuthTokenRequest);

    ADD_OPCODE_HANDLER(SMSG_CONNECTION_RETRY_TICKET,   STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_VERSION_RESULT,     STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_IP,                 STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,        STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_PUBLIC_KEY,                STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_REALMS_LIST,               STATUS_NEVER,    &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_AUTH_TOKEN_RESULT,         STATUS_NEVER,    &AuthSession::HandleServerSide);

	#undef ADD_OPCODE_HANDLER
}

AuthSession::AuthSession(QTcpSocket *socket) : SocketHandler(socket)
{
    m_logout = false;
    m_accountId = 0;
    m_username = QString();

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());

    QStringList ip = GetIp().split(".");

    WorldPacket data(SMSG_CLIENT_IP);

    for (quint8 i = 0; i < ip.size(); ++i)
        data << (quint8) ip.at(i).toUInt();

    SendPacket(data);
}

AuthSession::~AuthSession()
{
    OnClose();
}

void AuthSession::ProcessPacket()
{
    if (m_logout)
        return;

    QDataStream in(m_socket);

    while (m_socket->bytesAvailable())
    {
        if (m_packetSize == 0)
        {
            if (m_socket->bytesAvailable() < (qint64)sizeof(quint16))
                return;

            in >> m_packetSize;
        }

        if ((m_socket->bytesAvailable()) < (m_packetSize - 2))
            return;

        quint8 unk;
        quint16 opcode;
        QByteArray data;

        in >> unk;
        in >> opcode;
        data = in.device()->read((qint64)(m_packetSize - 5));

        if (AuthTable::Exists(opcode))
        {
            AuthHandler opcodeHandler = AuthTable::Get(opcode);
            Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, m_packetSize);

            WorldPacket packet(opcode, data);

            switch (opcodeHandler.status)
            {
            case STATUS_UNHANDLED:
                Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, data.size());
                break;
            case STATUS_NEVER:
                Log::Write(LOG_TYPE_DEBUG, "Received not allowed packet <%u> (size : %u).", opcode, data.size());
                break;
            default:
                if (opcodeHandler.status == STATUS_ALWAYS ||
                    (opcodeHandler.status == STATUS_AUTHED && m_accountId != 0))
                {
                    (this->*opcodeHandler.handler)(packet);
                    Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, data.size());
                }
                else
                {
                    // Report IP too
                    Log::Write(LOG_TYPE_DEBUG, "Warning ! Received packet with wrong status (hack !?) <%u> (size : %u).", opcode, data.size());
                    OnClose();
                }
                break;
            }
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, m_packetSize);

        m_packetSize = 0;
    }
}

void AuthSession::SendPacket(WorldPacket& data)
{
    data.WriteHeader();
    m_socket->write(data.GetPacket());

    Log::Write(LOG_TYPE_DEBUG, "Send packet %s <%u> (size : %u).", AuthTable::Get(data.GetOpcode()).name.toLatin1().data(), data.GetOpcode(), data.GetPacket().size());
}

void AuthSession::OnClose()
{
    m_logout = true;
    SocketHandler::OnClose();
    AuthServer::Instance()->RemoveSocket(this);
}

void AuthSession::HandleClientVersion(WorldPacket& packet)
{
    quint8 version, change;
    quint16 revision;
    QString build;

    packet >> version;
    packet >> revision;
    packet >> change;
    build =  packet.ReadString();

    QString clientVersion = QString(QString::number(version) + "." + QString::number(revision) + "." + QString::number(change));
    SendClientVersionResult(clientVersion, sAuthConfig->GetString("AcceptClientVersion"));
}

void AuthSession::SendClientVersionResult(QString clientVersion, QString expectedVersion)
{
    QStringList version = expectedVersion.split(".");

    WorldPacket data(SMSG_CLIENT_VERSION_RESULT);
    data << (quint8)(clientVersion == expectedVersion);
    data << (quint8)version.at(0).toUShort();
    data << (quint16)version.at(1).toUShort();
    data << (quint8)version.at(2).toUShort();
    data.WriteString("-1");
    SendPacket(data);
}

void AuthSession::HandlePublicKeyRequest(WorldPacket& /*packet*/)
{
    QByteArray publicKey = sCryptographyMgr->GetPublicKey();

    WorldPacket data(SMSG_PUBLIC_KEY);
    data << quint64(0x8000000000000000); // Salt
    data.WriteRawBytes(publicKey);
    SendPacket(data);
}

void AuthSession::HandleClientAuthentication(WorldPacket& packet)
{
    quint32 bufferSize;
    packet >> bufferSize;

    QByteArray buffer;
    buffer.resize(bufferSize);
    packet.ReadRawBytes(buffer.data(), buffer.size());

    WorldPacket decrypted(0, sCryptographyMgr->Decrypt(buffer));

    quint64 salt;
    decrypted >> salt;

    m_username = decrypted.ReadString();
    QString password = decrypted.ReadString();

    QSqlQuery result = sAuthDatabase->Query(SELECT_ACCOUNT_BY_USERNAME, QVariantList() << m_username);

    if (!result.first())
    {
        SendLoginErrorResult(LOGIN_RESULT_ERROR_INVALID_LOGIN);
        return;
    }

    QString hashPassword = result.value("hash_password").toString();

    if (Utils::HashPassword(m_username, password) != hashPassword)
    {
        SendLoginErrorResult(LOGIN_RESULT_ERROR_INVALID_LOGIN);
        return;
    }

    m_accountId = result.value("account_id").toUInt();

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(LOGIN_RESULT_SUCCESS);
    data << quint8(1); // hasAccountInformations
    data << int(COMMUNITY_FR); // Community
    data << quint8(0); // hasAdminInformations?

    std::unique_ptr<WakfuProto::Status> protoAccountStatus(new WakfuProto::Status);
    (*protoAccountStatus->mutable_status())["CGU"] = "5";
    (*protoAccountStatus->mutable_status())["TIMEZONE"] = "12500";
    (*protoAccountStatus->mutable_status())["WEAK_PASS"] = "1484654857";

    QByteArray protoAccountStatusBin;
    protoAccountStatusBin.resize((*protoAccountStatus).ByteSize());
    (*protoAccountStatus).SerializeToArray(protoAccountStatusBin.data(), protoAccountStatusBin.size());

    data.WriteRawBytes(protoAccountStatusBin);

    SendPacket(data);
}

void AuthSession::SendLoginErrorResult(LoginResult result)
{
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(result);
    data << quint8(0);
    data << quint8(0);
    SendPacket(data);
}

void AuthSession::HandleRealmsRequest(WorldPacket& /*packet*/)
{
    QSqlQuery result = sAuthDatabase->Query(SELECT_REALMS);

    WorldPacket data(SMSG_REALMS_LIST);
    Packet data2;

    data << result.size();

    while (result.next())
    {
        int realmId = result.value("realm_id").toInt();

        data << realmId;
        data.WriteString(result.value("name").toString(), STRING_SIZE_4);

        data << result.value("community").toInt();
        data.WriteString(result.value("address").toString(), STRING_SIZE_4);

        data << (int) 1;
        data << result.value("port").toInt();

        data << (quint8) realmId;

        data2 << realmId;
        data2.StartBlock<int>();
        {
            QStringList version = result.value("version").toString().split(".");
            data2 << (quint8)  version.at(0).toUShort();
            data2 << (quint16) version.at(1).toUShort();
            data2 << (quint8)  version.at(2).toUShort();
            data2.WriteString("-1");
        }
        data2.EndBlock<int>();

        data2.StartBlock<int>();
        {
            /* Config example
            COMMUNITY_CHECK_ENABLE 208 : "true"
            COMMUNITY_REQUIRED 209 : 0
            COMMUNITY_FORBIDDEN 210 : ""
            AUTHORIZED_PARTNERS 220 : "default"
            SERVER_ID 420 : 1
            */

            data2 << (int) 0;
        }
        data2.EndBlock<int>();

        data2 << (quint8) result.value("locked").toBool();
    }

    data << result.size();
    data.Append(data2);

    SendPacket(data);
}

void AuthSession::HandleAuthTokenRequest(WorldPacket& packet)
{
    quint32 serverId;
    quint64 accountId;

    packet >> serverId;
    packet >> accountId;

    QString token = Utils::GenerateToken(m_username);

    sAuthDatabase->Query(UPDATE_SESSION_TOKEN, QVariantList() << token << m_accountId);

    WorldPacket data(SMSG_AUTH_TOKEN_RESULT);
    data << (quint8) 0; // ResultCode
    data.WriteString(token, STRING_SIZE_4);
    SendPacket(data);
}

void AuthSession::HandleClientDisconnect(WorldPacket&)
{
    sAuthServer->RemoveSocket(this);
}
