#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Databases/Database.h"
#include "Miscellaneous/SharedDefines.h"
#include "Define.h"
#include "Network/SocketHandler.h"
#include "Entities/Character/Character.h"
#include "World/World.h"
#include "Scripting/ScriptMgr.h"

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
    quint8 charactersCount;
};

class Character;

class WorldSession : public SocketHandler
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    sAccountInfos GetAccountInfos() { return m_accountInfos; }

    void SetCharacter(Character* character) { m_character = character; }
    Character* GetCharacter() const { return m_character; }

    virtual void ProcessPacket();

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers
    void HandleClientDisconnect(WorldPacket& /*packet*/);
    void HandleClientVersion(WorldPacket& packet);
    void HandleClientAuthentication(WorldPacket& packet);
    void HandlePingCommand(WorldPacket& packet);
    void HandleInteractiveElement(WorldPacket& packet);
    void HandleGroupInvite(WorldPacket& packet);
    void HandleCharSelect(WorldPacket& packet);
    void HandleLeaveCharSelect(WorldPacket& /*packet*/);
    void HandleWhoisCommand(WorldPacket& packet);
    void HandleCharCreate(WorldPacket& packet);
    void HandleCharDelete(WorldPacket& packet);
    void HandleChatMessage(WorldPacket& packet);
    void HandlePrivateMessage(WorldPacket& packet);
    void HandleTradeMessage(WorldPacket& packet);
    void HandleRecruitMessage(WorldPacket& packet);
    void HandleCharMovement(WorldPacket& packet);
    void HandleCharDirection(WorldPacket& packet);
    void HandleCharEmote(WorldPacket& packet);
    void HandleSwitchChar(WorldPacket& /*packet*/);
    void HandleClientLanguage(WorldPacket& packet);
    void HandleServerTimeCommand(WorldPacket& /*packet*/);

    // SMSG Handlers
    void SendRSAPublicKey();
    void SendLoginErrorResult(LoginResult result);
    void SendWorldSelectResult();
    void SendServerTime();
    void SendCharactersList();
    void SendSelectCharacterResult(bool result);
    void SendEnterWorld();
    void SendCharacterStatsEnterWorld();
    void SendCharacterPosition();
    void SendUpdateObject();

public slots:
    void OnClose();

private:
    sAccountInfos m_accountInfos;
    Character* m_character;
};

#endif // WORLDSESSION_H
