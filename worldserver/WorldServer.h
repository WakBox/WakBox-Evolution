#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Game/Server/WorldSession.h"
#include "Utils/Singleton.h"

class WorldServer : public Singleton<WorldServer>
{
    Q_OBJECT
public:
    WorldServer();
    ~WorldServer();

    bool Initialize();

    bool Start(QHostAddress address, quint16 port);

private slots:
    void OnConnect();

private:
    QTcpServer* m_server;
};

#define sWorldServer WorldServer::Instance()

#endif // WORLDSERVER_H
