#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtNetwork>
#include <QTcpSocket>
#include "Packets/WorldPacket.h"
#include "Opcodes/Opcodes.h"

class WorldPacket;

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    SocketHandler(QTcpSocket* socket);

    QString GetIp() const
    {
        return m_socket->peerAddress().toString();
    }

    virtual void ProcessPacket(WorldPacket& packet) = 0;
    void SendPacket(const WorldPacket& data) const;

public slots:
    void OnRead();
    void OnDisconnect();

    virtual void OnClose();
    virtual void OnError(QAbstractSocket::SocketError error);

protected:
    QTcpSocket* m_socket;
};

#endif // SOCKETREADER_H
