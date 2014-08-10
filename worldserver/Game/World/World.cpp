#include "World.h"
#include "Game/Entities/ObjectMgr.h"
#include "Game/Scripting/ScriptMgr.h"

#include "Utils/Util.h"

template<> World*  Singleton<World>::m_instance = 0;

World::World()
{
    m_running = true;
}

World::~World()
{
    SessionList::Iterator itr, next;
    for (itr = m_sessions.begin(); itr != m_sessions.end(); itr = next)
    {
        next = itr;
        ++next;

        delete (*itr);
        m_sessions.erase(itr);
    }

    m_running = false;
}

bool World::Initialize()
{
    ObjectMgr::Instance()->SetHighestGuids();
    ObjectMgr::Instance()->LoadInteractiveElements();

    ScriptMgr::Instance()->Initialize();
    return true;
}

void World::AddSession(WorldSession *session)
{
    m_sessions.push_back(session);
}

void World::RemoveSession(WorldSession* session)
{
    m_sessions.removeOne(session);
}

void World::Update(quint64 diff)
{
    ScriptMgr::Instance()->OnUpdate(diff);
}
