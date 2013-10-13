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

void WorldSession::ProcessPacket(WorldPacket& /*packet*/)
{
}

void WorldSession::OnClose()
{
    World::Instance()->RemoveSession(this);
    SocketHandler::OnClose();
}
