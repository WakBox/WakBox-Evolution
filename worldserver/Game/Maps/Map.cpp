#include "Map.h"

Map::Map(qint32 id)
{
    m_id = id;
}

Map::~Map()
{

}

Partition* Map::CreatePartition(qint32 id)
{
    Partition* partition = FindPartition(id);

    if (!partition)
    {
        partition = new Partition(this, id);
        partition->Load();

        m_partitions[id] = partition;
    }

    return partition;
}

void Map::AddCharacterToMap(Character* character)
{
    character->SetMap(this);

    Partition* partition = CreatePartition(character->GetLastPartitionId());
    partition->AddCharacterToPartition(character);
}
