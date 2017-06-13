#include "Map.h"
#include "Entities/Character/Character.h"
#include "Entities/ObjectMgr.h"
#include "Utils/Util.h"

Map::Map(qint16 id)
{
    m_id = id;
}

Map::~Map()
{

}

void Map::Load()
{
    CreatureGuidsHash mapCreatureGuids = sObjectMgr->GetMapCreatureGuids(GetId());

    // Don't load all partition (need a partition class that do the following)
    for (CreatureGuidsHash::ConstIterator partition = mapCreatureGuids.begin(); partition != mapCreatureGuids.end(); ++partition)
    {
        QList<qint64> creatureGuids = partition.value();

        for (QList<qint64>::ConstIterator guid = creatureGuids.begin(); guid != creatureGuids.end(); ++guid)
        {
            Creature* creature = new Creature();
            creature->SetGuid(*guid);
            creature->SetData(sObjectMgr->GetCreatureData(*guid));

            m_mapObjects[Utils::getIntFromTwoInt(creature->GetPositionX(), creature->GetPositionY())].push_back(creature);
        }
    }
}

void Map::AddCharacterToMap(Character* character)
{
    m_mapObjects[Utils::getIntFromTwoInt(character->GetPositionX(), character->GetPositionY())].push_back(character);
    character->SetMap(this);

    // Send all creature / player in the area
    character->GetSession()->SendActorSpawn();

    // Send actor spawn to the other player in the area
    character->GetSession()->SendActorSpawn(character->GetSession());

    character->SetInWorld();
}

void Map::SendPacket(WorldPacket &data, WorldSession *self)
{
    QList<Unit*>::ConstIterator itr;
    qint16 partition = Utils::getIntFromTwoInt(self->GetCharacter()->GetPositionX(), self->GetCharacter()->GetPositionY());

    for (itr = m_mapObjects[partition].begin(); itr != m_mapObjects[partition].end(); ++itr)
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
