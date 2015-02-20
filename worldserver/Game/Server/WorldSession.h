#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Databases/Database.h"
#include "Miscellaneous/SharedDefines.h"
#include "Define.h"
#include "Network/SocketHandler.h"
#include "World/World.h"
#include "Scripting/ScriptMgr.h"

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
    virtual void SendPacket(WorldPacket& data);

    // Default handlers
    void HandleNULL(WorldPacket& /*packet*/) {}
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG handlers
    void HandleClientVersion(WorldPacket& packet);
    void HandlePublicKeyRequest(WorldPacket& /*packet*/);
    void HandleClientAuthToken(WorldPacket& packet);
    void HandleAuthTokenRequest(WorldPacket& packet);


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
    void HandleStartFight(WorldPacket& packet);
    void HandleSwitchChar(WorldPacket& /*packet*/);
    void HandleClientLanguage(WorldPacket& packet);
    void HandleServerTimeCommand(WorldPacket& /*packet*/);

    // SMSG handlers
    void SendClientVersionResult(QString clientVersion, QString expectedVersion);
    void SendWorldSelectResult(bool result);
    void SendClientCalendarSync();
    void SendSystemConfiguration();
    void SendAdditionalSlotsUpdate();
    void SendCharactersList();
    void SendCompanionList();

    //
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
