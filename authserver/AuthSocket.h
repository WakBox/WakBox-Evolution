#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Define.h"
#include "Databases/Database.h"
#include "Network/SocketHandler.h"

class AuthSocket : public SocketHandler
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    ~AuthSocket();

    virtual void ProcessPacket();
    void HandlePacket(quint16 opcode, WorldPacket& packet);

public slots:
    virtual void OnClose();

private:

};

#endif // AUTHSOCKET_H
