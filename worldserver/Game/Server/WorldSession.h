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
    LOGIN_RESULT_SUCCESS                    = 0,
    LOGIN_RESULT_INVALID_LOGIN              = 2,
    LOGIN_RESULT_ALREADY_CONNECTED          = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS          = 4,
    LOGIN_RESULT_ACCOUNT_BANNED             = 5,
    LOGIN_RESULT_ACCOUNT_LOCKED             = 9,
    LOGIN_RESULT_SERVER_DOWN                = 10,
    LOGIN_RESULT_TOO_MANY_CONNECTIONS       = 11,
    LOGIN_RESULT_INVALID_PARTNER            = 12,
    LOGIN_RESULT_INVALID_MAIL               = 20,
    LOGIN_RESULT_ACCOUNT_UNDER_MODERATION   = 21,
    LOGIN_RESULT_CLOSED_BETA                = 127
};

struct sAccountInfos
{
    quint64 id;
    QString username;
    QString pseudo;
    quint8 gmLevel;
    qint64 subscriptionTime;
};

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    sAccountInfos GetAccountInfos() { return m_accountInfos; }

    virtual void ProcessPacket();

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers
    void HandleClientVersion(WorldPacket& packet);
    void HandleClientAuthentication(WorldPacket& packet);
    void HandleWorldSelect(WorldPacket& packet);
    void HandleLeaveCharSelect(WorldPacket& /*packet*/);
    void HandleCharCreate(WorldPacket& packet);
    void HandleCharDelete(WorldPacket& packet);
    void HandleSecretAnswerResponse(WorldPacket& packet);

    // SMSG Handlers

    void SendRSAPublicKey();
    void SendLoginErrorResult(LoginResult result);
    void SendWorldList();
    void SendServerTime();
    void SendCharactersList();
    void SendCharDeleteResult(quint64 guid, quint8 success);
    void SendSecretAnswerRequest();

public slots:
    void OnClose();

private:
    sAccountInfos m_accountInfos;
};

#endif // WORLDSESSION_H
