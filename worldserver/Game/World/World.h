#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "WorldServer.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Utils/Singleton.h"

class WorldSession;

typedef QList<WorldSession*> SessionList;

class World : public Singleton<World>
{
public:
    World();
    ~World();

    bool Initialize();
    bool IsRunning() { return m_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);

private:
    bool m_running;
    SessionList m_sessions;
};

#endif
