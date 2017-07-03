#ifndef MAP_H
#define MAP_H

#include <QtCore>

#include "Entities/ObjectMgr.h"
#include "Partition.h"

typedef QHash<qint32/*partitionId*/, Partition*> PartitionHash;

class Map
{
public:
    Map(qint32 id);
    ~Map();

    qint16 GetId() { return m_id; }

    Partition* CreatePartitionFromCell(qint32 x, qint32 y);
    Partition* CreatePartition(qint32 id, bool createAdjacent = false);
    Partition* FindPartition(qint32 id) const
    {
        PartitionHash::const_iterator it = m_partitions.find(id);
        return (it != m_partitions.end() ? it.value() : nullptr);
    }

    void AddCharacterToMap(Character* character);

private:
    qint32 m_id;
    PartitionHash m_partitions;
};

#endif // MAP_H
