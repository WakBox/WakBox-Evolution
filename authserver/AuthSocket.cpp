#include "AuthSocket.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"

AuthSocket::AuthSocket(QTcpSocket *socket) : SocketHandler(socket)
{
    m_keyPair = NULL;
    m_cert = NULL;

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

        qint8 unk;
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
        qint8 version, change;
        qint16 revision;
        QString build;
        qint8 buildSize;

        packet >> version;
        packet >> revision;
        packet >> change;
        packet >> buildSize;

        build = packet.ReadString(buildSize);

        QString clientVersion = QString(QString::number(version) + "." + QString::number(revision)
                                        + "." + QString::number(change) + "." + build);
        qDebug() << clientVersion;

        SendRSAPacket();
    } break;

    case CMSG_CLIENT_AUTH:

        return SendLoginResultPacket();

        qint64 rsaVerification;
        qint8 usernameLength, passwordLength;
        QString username, password;

        packet >> rsaVerification;
        packet >> usernameLength;
        username = packet.ReadString(usernameLength);
        packet >> passwordLength;
        password = packet.ReadString(passwordLength);
        break;
    }
}

void AuthSocket::SendRSAPacket()
{
    WorldPacket data(SMSG_RSA_PUBLIC_KEY, Utils::FromHexString("00 AE 04 08 80 00 00 00 00 00 00 00 30 81 9F 30 0D 06 09 2A 86 48 86 F7 0D 01 01 01 05 00 03 81 8D 00 30 81 89 02 81 81 00 8A C8 54 B6 F8 0A 47 1B AA A4 81 27 53 B5 74 4F E1 52 91 38 87 4C 20 0F 96 2B 2F A4 7A 2E 00 28 EA A2 B9 9F 68 EB D3 94 57 0A 06 50 13 E7 B8 E0 B8 0A 16 B5 1C 24 84 1F A4 E0 0A 26 58 F6 1B 54 58 6A 56 F9 89 BB F0 A5 83 43 7A AD BD 95 4A BC B6 6B 5E 85 B1 B9 99 E5 6C 8E 46 C4 2B DC 43 0D 63 F6 71 F7 16 E9 25 36 05 3C 0A 89 19 B6 03 BC CF AC C7 CB 14 06 71 7C 2F D5 DB 23 8F C6 D7 19 02 03 01 00 01"));
    SendPacket(data);
}

void AuthSocket::SendLoginResultPacket()
{
    // too much bytes (+5), must be size 68
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << qint8(0);
    data << qint16(61); // data length
    data << qint8(1);

    for (quint8 i = 0; i < 4; ++i)
        data << qint8(0);

    data << qint8(6);

    for (quint8 i = 0; i < 5; ++i)
        data << qint8(0);

    data << qint8(4);
    data << qint8(102);
    data << qint8(43);
    data << qint8(64);

    for (quint8 i = 0; i < 29; ++i)
        data << qint8(0);

    data << qint8(11); // Player name length
    data << "SuperM0nkey";

    data << qint8(2);
    data << qint8(63);
    data << qint8(63);
    data << qint8(0);
    data << qint8(0);

    SendPacket(data);
}
