#include "AuthSocket.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Cryptography/Cryptography.h"

AuthSocket::AuthSocket(QTcpSocket *socket) : SocketHandler(socket)
{
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

AuthSocket::~AuthSocket()
{
}

void AuthSocket::ProcessPacket()
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

        if ((m_socket->bytesAvailable() + 2) < m_packetSize)
            return;

        quint8 unk;
        quint16 opcode;

        in >> unk;
        in >> opcode;

        if (OpcodeTable::Exists(opcode))
        {
            Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", OpcodeTable::Get(opcode).name.toLatin1().data(), opcode, m_packetSize);

            WorldPacket packet(opcode, in.device()->readAll());
            HandlePacket(opcode, packet);
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet opcode %u (size : %u).", opcode, m_packetSize);

        m_packetSize = 0;
    }
}

void AuthSocket::OnClose()
{
    AuthServer::Instance()->RemoveSocket(this);
    SocketHandler::OnClose();
}

void AuthSocket::HandlePacket(quint16 opcode, WorldPacket& packet)
{
    switch (opcode)
    {
    case CMSG_CLIENT_DISCONNECT:
        break;

    case CMSG_CLIENT_VERSION:
    {
        quint8 version, change;
        quint16 revision;
        QString build;

        packet >> version;
        packet >> revision;
        packet >> change;

        build = packet.ReadString();

        QString clientVersion = QString(QString::number(version) + "." + QString::number(revision)
                                        + "." + QString::number(change) + "." + build);
        qDebug() << clientVersion;

        SendRSAPacket();
    } break;

    case CMSG_CLIENT_AUTH:
        QByteArray buffer;
        buffer.resize(packet.GetPacket().length());
        packet.ReadRawBytes(buffer.data(), buffer.size());

        WorldPacket decrypted(0, Cryptography::Instance()->Decrypt(buffer));

        quint64 rsaVerification;
        decrypted >> rsaVerification;

        QString account = decrypted.ReadString();
        QString password = decrypted.ReadString();

        SendLoginResultPacket(account, password);

        break;
    }
}

void AuthSocket::SendRSAPacket()
{
    QByteArray publicKey = Cryptography::Instance()->GetPublicKey();

    WorldPacket data(SMSG_RSA_PUBLIC_KEY);
    data << quint64(0x8000000000000000);
    data.WriteRawBytes(publicKey.data(), publicKey.length());
    SendPacket(data);
}

void AuthSocket::SendLoginResultPacket(QString account, QString password)
{
    QSqlQuery result = Database::Auth()->Query(SELECT_ACCOUNT_BY_USERNAME, QVariantList() << account);
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    LoginResult loginResult = LOGIN_RESULT_INVALID_LOGIN;

    if (!result.first())
    {
        data << (quint8)loginResult;
        SendPacket(data);
        return;
    }

    QSqlRecord fields = result.record();
    QString hashPassword = result.value(fields.indexOf("hash_password")).toString();

    qDebug() << hashPassword;
    qDebug() << Utils::HashPassword(account, password);
    if (Utils::HashPassword(account, password) == hashPassword)
    {
        loginResult = LOGIN_RESULT_SUCCESS;
    }

    data << (quint8)loginResult;

    switch (loginResult)
    {
    case LOGIN_RESULT_ACCOUNT_BANNED:
        break;

    case LOGIN_RESULT_SUCCESS:
        data << quint16(50);
        data << quint8(1);
        data << quint8(0);
        data << quint32(6);
        data << quint8(0);
        data << quint64(result.value(fields.indexOf("account_id")).toULongLong());
        data << quint8(0);
        data << quint64(1000); // Subscribe
        data << quint32(0); // isAdmin ? 1 : 0
        data.WriteString(account);
        data.WriteString("??");
        data << quint16(00);
        break;
    default:
        break;
    }

    SendPacket(data);
}
