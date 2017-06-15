#ifndef OBJECTMGR_H
#define OBJECTMGR_H

#include <QtCore>
#include "Databases/Database.h"
#include "Utils/Singleton.h"
#include "Entities/Creature/Creature.h"

enum GuidType
{
    GUIDTYPE_NONE      = 0,
    GUIDTYPE_CHARACTER = 1
};

typedef QHash<qint64/*guid*/, CreatureData> CreatureDataHash;
typedef QHash<qint16/*partitionId*/, QList<qint64>> CreatureGuidsHash;
typedef QHash<qint16/*mapId*/, CreatureGuidsHash> MapCreatureGuidsHash;

typedef QHash<quint32, QString> InteractiveElementsHash;

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

    CreatureData const& GetCreatureData(qint64 guid)
    {
        return m_creatureData[guid];
    }

    QList<qint64> const& GetPartitionCreatureGuids(qint16 mapId, qint16 partition)
    {
        return m_mapCreatureGuids[mapId][partition];
    }

    void LoadCreatures();
    void LoadInteractiveElements();
    const QString GetInteractiveElementScriptNameById(quint32 id)
    {
        return m_interactiveElements.value(id, QString());
    }

private:
    quint32 m_highCharacterGuid;

    CreatureDataHash m_creatureData;
    CreatureGuidsHash m_paritionCreatureGuids;
    MapCreatureGuidsHash m_mapCreatureGuids;

    InteractiveElementsHash m_interactiveElements;
};

#define sObjectMgr ObjectMgr::Instance()

#endif // OBJECTMGR_H
