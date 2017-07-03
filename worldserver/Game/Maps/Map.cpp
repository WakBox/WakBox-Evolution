#include "Map.h"
#include "MapMgr.h"

Map::Map(qint32 id)
{
    m_id = id;
}

Map::~Map()
{

}

Partition* Map::CreatePartitionFromCell(qint32 x, qint32 y)
{
    return CreatePartition(Utils::getIntFromTwoInt(sMapMgr->getMapCoordFromCell(x), sMapMgr->getMapCoordFromCell(y)));
}

Partition* Map::CreatePartition(qint32 id, bool createAdjacent)
{
    Partition* partition = FindPartition(id);

    if (!partition)
    {
        partition = new Partition(this, id);
        partition->Load();

        if (createAdjacent)
        {
            qint32 x = Utils::getFirstShortFromInt(id);
            qint32 y = Utils::getSecondShortFromInt(id);

            CreatePartitionFromCell(x, y + 1);
            CreatePartitionFromCell(x - 1, y + 1);
            CreatePartitionFromCell(x + 1, y + 1);
            CreatePartitionFromCell(x - 1, y);
            CreatePartitionFromCell(x + 1, y);
            CreatePartitionFromCell(x, y - 1);
            CreatePartitionFromCell(x - 1, y - 1);
            CreatePartitionFromCell(x + 1, y - 1);
        }

        m_partitions[id] = partition;

        qDebug() << "Partition [" << id << "] created.";
    }

    return partition;
}

void Map::AddCharacterToMap(Character* character)
{
    character->SetMap(this);

    Partition* partition = CreatePartition(character->GetLastPartitionId(), true);
    partition->AddCharacterToPartition(character);
}
