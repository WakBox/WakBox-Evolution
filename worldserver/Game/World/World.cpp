#include "World.h"

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

