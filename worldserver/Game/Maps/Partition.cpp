#include "Partition.h"
#include "Entities/ObjectMgr.h"
#include "Map.h"
#include "Maps/MapMgr.h"

Partition::Partition(Map* map, qint16 partitionId)
{
    m_map = map;
    m_id = partitionId;
}

Partition::~Partition()
{

}

void Partition::Load()
{
    QList<qint64> const& creatureGuids = sObjectMgr->GetPartitionCreatureGuids(GetMap()->GetId(), GetId());

    qDebug() << "CreatureGuids = " << creatureGuids.size();

    for (QList<qint64>::ConstIterator guid = creatureGuids.begin(); guid != creatureGuids.end(); ++guid)
    {
        Creature* creature = new Creature();
        creature->SetGuid(*guid);
        creature->SetData(sObjectMgr->GetCreatureData(*guid));

        qDebug() << "partitionId " << Utils::getIntFromTwoInt(
                        MapMgr::getMapCoordFromCell(creature->GetPositionX()),
                        MapMgr::getMapCoordFromCell(creature->GetPositionY()));

        m_unitList.push_back(creature);
    }
}

void Partition::AddCharacterToPartition(Character* character)
{
    m_unitList.push_back(character);
    character->SetPartition(this);
}

void Partition::SendPacket(WorldPacket &data, WorldSession *self)
{
    for (MapUnitList::ConstIterator itr = m_unitList.begin(); itr != m_unitList.end(); ++itr)
    {
        if ((*itr) &&
             (*itr)->GetTypeId() == TYPEID_CHARACTER &&
             (*itr)->ToCharacter() &&
             (*itr)->ToCharacter()->GetSession() != self)
        {
            (*itr)->ToCharacter()->GetSession()->SendPacket(data);
        }
    }
}
