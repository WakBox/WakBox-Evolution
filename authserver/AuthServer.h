#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "AuthSession.h"
#include "Utils/Singleton.h"

typedef QList<AuthSession*> SocketList;

class AuthServer : public Singleton<AuthServer>
{
    Q_OBJECT
public:
    AuthServer();
    ~AuthServer();

    bool Initialize();
    bool Start(QHostAddress address, quint16 port);

    void RemoveSocket(AuthSession* socket);

private slots:
    void OnConnect();

private:
    QTcpServer* m_server;
    SocketList m_sockets;
};

#define sAuthServer AuthServer::Instance()

#endif // WORLDSERVER_H
