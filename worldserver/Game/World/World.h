#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "WorldServer.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Utils/Singleton.h"
#include "Server/WorldSession.h"
#include "Entities/Character/Character.h"

class WorldSession;
class Character;

typedef QList<WorldSession*> SessionList;
typedef QHash<QString, Character*> CharacterNameMap;

class World : public Singleton<World>
{
public:
    World();
    ~World();

    bool Initialize();
    bool IsRunning() { return m_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);
    const SessionList& GetAllSessions() const { return m_sessions; }

    void AddCharacter(QString name, Character* character) { m_characters.insert(name, character); }
    void RemoveCharacterByName(QString name) { m_characters.remove(name); }
    Character* FindCharacterByName(QString name)
    {
        return m_characters.contains(name) ? m_characters.value(name) : nullptr;
    }

    void Update(quint64 diff);

    void SendGlobalPacket(WorldPacket& data, WorldSession* self = nullptr);

private:
    bool m_running;
    SessionList m_sessions;
    CharacterNameMap m_characters;
};

#define sWorld World::Instance()

#endif
