#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Databases/Database.h"
#include "Define.h"
#include "Network/SocketHandler.h"
#include "World/world.h"

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    virtual void ProcessPacket(WorldPacket& packet);

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers

    // SMSG Handlers

public slots:
    void OnClose();

private:

};

#endif // WORLDSESSION_H
