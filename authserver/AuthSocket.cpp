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
        quint64 rsaVerification;
        QString username, password;

        uint bufferLen = packet.GetPacket().length();
        qDebug() << bufferLen;
        char* b = new char[bufferLen];
        packet.ReadRawBytes(b, bufferLen);
        qDebug() << b;

        QByteArray decoded = Cryptography::Instance()->Decrypt(b, bufferLen);

        /*
        packet >> rsaVerification;
        qDebug() << rsaVerification;

        username = packet.ReadString();
        password = packet.ReadString();*/
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

void AuthSocket::SendLoginResultPacket()
{
    // too much bytes (+5), must be size 68
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(0);
    data << quint16(61); // data length
    data << quint8(1);

    for (quint8 i = 0; i < 4; ++i)
        data << quint8(0);

    data << quint8(6);

    for (quint8 i = 0; i < 5; ++i)
        data << quint8(0);

    data << quint8(4);
    data << quint8(102);
    data << quint8(43);
    data << quint8(64);

    for (quint8 i = 0; i < 29; ++i)
        data << quint8(0);

    data << quint8(11); // Pseudo length
    data << "WakSandbox0";

    data << quint8(2);
    data << quint8(63);
    data << quint8(63);
    data << quint8(0);
    data << quint8(0);

    SendPacket(data);
}
