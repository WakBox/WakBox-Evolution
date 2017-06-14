#ifndef MAP_H
#define MAP_H

#include <QtCore>

#include "Entities/ObjectMgr.h"
#include "Partition.h"

typedef QHash<qint16/*partitionId*/, Partition*> PartitionHash;

class Map
{
public:
    Map(qint16 id);
    ~Map();

    qint16 GetId() { return m_id; }

    QList<qint64> const& GetPartitionCreatureGuids(qint16 partition)
    {
        CreatureGuidsHash const& partitionCreatureGuids = sObjectMgr->GetMapCreatureGuids(GetId());
        return partitionCreatureGuids[partition];
    }

    Partition* CreatePartition(qint16 id);
    Partition* FindPartition(qint16 id) const
    {
        PartitionHash::const_iterator it = m_partitions.find(id);
        return (it != m_partitions.end() ? it.value() : nullptr);
    }

    void AddCharacterToMap(Character* character);

private:
    qint16 m_id;
    PartitionHash m_partitions;
};

#endif // MAP_H
