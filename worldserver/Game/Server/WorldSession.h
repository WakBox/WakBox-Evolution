#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Databases/Database.h"
#include "Define.h"
#include "Network/SocketHandler.h"
#include "World/world.h"

enum LoginResult
{
    LOGIN_RESULT_SUCCESS                = 0,
    LOGIN_RESULT_INVALID_LOGIN          = 2,
    LOGIN_RESULT_ALREADY_CONNECTED      = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS      = 4,
    LOGIN_RESULT_ACCOUNT_BANNED         = 5
    // etc.
};

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    virtual void ProcessPacket();

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers
    void HandleClientVersion(WorldPacket& packet);
    void HandleClientAuthentication(WorldPacket& packet);
    void HandleWorldSelect(WorldPacket& packet);

    // SMSG Handlers

    void SendRSAPublicKey();
    void SendLoginResult();
    void SendWorldList();

public slots:
    void OnClose();

private:

};

#endif // WORLDSESSION_H
