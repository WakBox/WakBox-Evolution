#include "World.h"
#include "BinaryData/BinaryData.h"
#include "Maps/TopologyMgr.h"
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
    sAuthDatabase->Query(UPDATE_REALM_LOCKED, QVariantList() << 1 << sWorldConfig->GetInt("RealmId"));

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
    LoadBinaryStorage();

    // Test
    if (AchievementBinaryData const* achievement = sAchievementStorage.FindEntry(2517))
    {
        qDebug() << "Achievement " << achievement->m_id << " found!";
        qDebug() << "Criteron: " << achievement->m_criterion;
    }

    sTopologyMgr->LoadTopology();

    sObjectMgr->SetHighestGuids();
    sObjectMgr->LoadInteractiveElements();

    sScriptMgr->Initialize();

    sAuthDatabase->Query(UPDATE_REALM_LOCKED, QVariantList() << 0 << sWorldConfig->GetInt("RealmId"));

    return true;
}

void World::AddSession(WorldSession *session)
{
    m_sessions.push_back(session);

    QStringList ip = session->GetIp().split(".");

    WorldPacket data(SMSG_CLIENT_IP);

    for (quint8 i = 0; i < ip.size(); ++i)
        data << (quint8) ip.at(i).toUInt();

    session->SendPacket(data);
}

void World::RemoveSession(WorldSession* session)
{
    m_sessions.removeOne(session);
}

void World::Update(quint64 diff)
{
    sScriptMgr->OnUpdate(diff);
}

void World::SendGlobalPacket(WorldPacket &data, WorldSession *self)
{
    SessionList::ConstIterator itr;
    for (itr = m_sessions.begin(); itr != m_sessions.end(); ++itr)
    {
        if (((*itr) &&
             (*itr)->GetCharacter() &&
             (*itr)->GetCharacter()->IsInWorld()) &&
             (*itr) != self)
        {
            (*itr)->SendPacket(data);
        }
    }
}
