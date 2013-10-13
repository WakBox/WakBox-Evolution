#include "AuthSocket.h"
#include "AuthServer.h"
#include "Utils/Util.h"
#include "Opcodes/Opcodes.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"

AuthSocket::AuthSocket(QTcpSocket *socket) : SocketHandler(socket)
{
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

AuthSocket::~AuthSocket() {}

void AuthSocket::OnClose()
{
    AuthServer::Instance()->RemoveSocket(this);
    SocketHandler::OnClose();
}

void AuthSocket::ProcessPacket(WorldPacket& /*packet*/)
{

}
