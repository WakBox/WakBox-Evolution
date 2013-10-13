#include "SocketHandler.h"
#include "Logs/Log.h"

SocketHandler::SocketHandler(QTcpSocket *socket)
{
    m_socket = socket;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

void SocketHandler::OnRead()
{

}

void SocketHandler::OnDisconnect()
{

}

void SocketHandler::OnClose()
{
    Log::Write(LOG_TYPE_NORMAL, "Closing connection with %s", m_socket->peerAddress().toString().toLatin1().data());
    m_socket->deleteLater();
}

void SocketHandler::OnError(QAbstractSocket::SocketError /*error*/)
{

}

void SocketHandler::SendPacket(const WorldPacket& data) const
{
    m_socket->write(data.GetPacket());
}
