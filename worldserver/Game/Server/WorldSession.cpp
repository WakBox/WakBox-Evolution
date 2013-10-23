#include "WorldSession.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "World/World.h"

WorldSession::WorldSession(QTcpSocket *socket) : SocketHandler(socket)
{
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

WorldSession::~WorldSession()
{
}

void WorldSession::ProcessPacket()
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
            opcodeHandler handler = OpcodeTable::Get(opcode).handler;
            WorldPacket packet(opcode, in.device()->readAll());

            (this->*handler)(packet);
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u>.", opcode);

        m_packetSize = 0;
    }
}

void WorldSession::OnClose()
{
    World::Instance()->RemoveSession(this);
    SocketHandler::OnClose();
}
