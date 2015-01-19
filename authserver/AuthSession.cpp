#include "AuthSession.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Cryptography/CryptographyMgr.h"

AuthHandlerMap  AuthTable::authHandlers;

void AuthTable::InitHandlers()
{
    #define ADD_OPCODE_HANDLER(opcode, handler) \
        AddOpcodeHandler(opcode, #opcode, handler);

    ADD_OPCODE_HANDLER(CMSG_CLIENT_DISCONNECT,                      &AuthSession::HandleClientDisconnect);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                         &AuthSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_AUTH,                            &AuthSession::HandleClientAuthentication);
    ADD_OPCODE_HANDLER(CMSG_PUBLIC_KEY_REQUEST,                     &AuthSession::HandlePublicKeyRequest);
    ADD_OPCODE_HANDLER(CMSG_REALMS_REQUEST,                         &AuthSession::HandleRealmsRequest);

    ADD_OPCODE_HANDLER(SMSG_CONNECTION_RETRY_TICKET,                &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_VERSION_RESULT,                  &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,                     &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_PUBLIC_KEY,                             &AuthSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_REALMS_LIST,                            &AuthSession::HandleServerSide);
}

AuthSession::AuthSession(QTcpSocket *socket) : SocketHandler(socket)
{
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

AuthSession::~AuthSession()
{
}

void AuthSession::ProcessPacket()
{
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
            (this->*opcodeHandler.handler)(packet);
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
    AuthServer::Instance()->RemoveSocket(this);
    SocketHandler::OnClose();
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
    qDebug() << "Received version packet : " << clientVersion << " build : " << build;

    SendClientVersionResult(clientVersion, sWorldConfig->GetString("AcceptClientVersion"));
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
    data << quint64(0x8000000000000000);
    data.WriteRawBytes(publicKey.data(), publicKey.length());
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

    quint64 rsaVerification;
    decrypted >> rsaVerification;

    QString account = decrypted.ReadString();
    QString password = decrypted.ReadString();

    QSqlQuery result = sAuthDatabase->Query(SELECT_ACCOUNT_BY_USERNAME, QVariantList() << account);

    if (!result.first())
    {
        SendLoginErrorResult(LOGIN_RESULT_ERROR_INVALID_LOGIN);
        return;
    }

    QSqlRecord fields = result.record();
    QString hashPassword = result.value(fields.indexOf("hash_password")).toString();

    if (Utils::HashPassword(account, password) != hashPassword)
    {
        SendLoginErrorResult(LOGIN_RESULT_ERROR_INVALID_LOGIN);
        return;
    }

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(LOGIN_RESULT_SUCCESS);
    data << quint8(0); // m_activateSteamLinkHint (bool)
    data << quint8(1); // hasAccountInformations
    data << int(COMMUNITY_FR); // Community
    data << quint8(0); // hasAdminInformations?
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
    data << result.size();

    while (result.next())
    {
        QSqlRecord fields = result.record();

        data << result.value(fields.indexOf("realm_id")).toInt();
        data.WriteString(result.value(fields.indexOf("name")).toString(), STRING_SIZE_4);

        data << result.value(fields.indexOf("community")).toInt();
        data.WriteString(result.value(fields.indexOf("address")).toString(), STRING_SIZE_4);

        data << int(1);
        data << result.value(fields.indexOf("port")).toInt();

        data << result.value(fields.indexOf("realm_id")).toInt();
    }



    SendPacket(data);
}

void AuthSession::HandleClientDisconnect(WorldPacket&)
{
    // TODO
}


