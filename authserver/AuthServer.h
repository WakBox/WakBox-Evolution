#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QtNetwork>

#include "AuthSocket.h"
#include "Utils/Singleton.h"

typedef QList<AuthSocket*> SocketList;

class AuthServer : public Singleton<AuthServer>
{
    Q_OBJECT
public:
    AuthServer();
    ~AuthServer();

    bool Initialize();
    bool Start(QHostAddress address, quint16 port);

    void RemoveSocket(AuthSocket* socket);

private slots:
    void OnConnect();

private:
    QTcpServer* m_server;
    SocketList m_sockets;
};

#endif // AUTHSERVER_H
