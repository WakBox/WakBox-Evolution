#include "ObjectMgr.h"
#include "Configuration/ConfigMgr.h"
#include "Logs/Log.h"
#include "Utils/Util.h"
#include "Define.h"
#include "Maps/MapMgr.h"

template<> ObjectMgr*  Singleton<ObjectMgr>::m_instance = 0;

ObjectMgr::ObjectMgr()
{
    m_highCharacterGuid = 0;
}

ObjectMgr::~ObjectMgr() {}

void ObjectMgr::SetHighestGuids()
{
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTER_MAX_GUID);
    if (result.first())
        m_highCharacterGuid = result.value(0).toUInt();
}

quint32 ObjectMgr::GenerateGuid(GuidType type)
{
    switch (type)
    {
        case GUIDTYPE_CHARACTER:
        {
            Q_ASSERT(m_highCharacterGuid < 0xFFFFFFFE && "ObjectMgr::GenerateGuid : character guid overflow !");
            return ++m_highCharacterGuid;
        }
        default:
            Q_ASSERT(false && "ObjectMgr::GenerateGuid : unknown guid type.");
            return 0;
    }
}

void ObjectMgr::LoadCreatures()
{
    QTime t;
    t.start();

    QSqlQuery result = sWorldDatabase->Query(SELECT_CREATURES);

    while (result.next())
    {
        // Check if creature in MonsterBinaryData

        CreatureData data;
        data.id = quint32(result.value("breed").toUInt());
        data.level = quint16(result.value("level").toUInt());
        data.position_x = qint32(result.value("position_x").toInt());
        data.position_y = qint32(result.value("position_y").toInt());
        data.position_z = qint16(result.value("position_z").toInt());
        data.direction = quint8(result.value("direction").toUInt());
        data.instance_id = qint32(result.value("instance_id").toInt());
        data.group_id = quint32(result.value("group_id").toUInt());
        m_creatureData[qint64(result.value("guid").toLongLong())] = data;

        // Check if instance_id exists

        // Add to map/partition
        qint16 partitionId = Utils::getIntFromTwoInt(
                    MapMgr::getMapCoordFromCell(data.position_x),
                    MapMgr::getMapCoordFromCell(data.position_y));

        QList<qint64>& partitionCreatureGuids = m_mapCreatureGuids[data.instance_id][partitionId];
        partitionCreatureGuids.push_back(qint64(result.value("guid").toLongLong()));
    }

    Log::Write(LOG_TYPE_NORMAL, ">> Loaded %u creatures in %u ms.", m_creatureData.count(), t.elapsed());

}

void ObjectMgr::LoadInteractiveElements()
{
    QTime t;
    t.start();

    QSqlQuery result = sWorldDatabase->Query(SELECT_INTERACTIVE_ELEMENTS);

    while (result.next())
        m_interactiveElements[(quint32)result.value("interactive_element_id").toUInt()] = result.value("script_name").toString();

    Log::Write(LOG_TYPE_NORMAL, ">> Loaded %u interactive elements in %u ms.", m_interactiveElements.count(), t.elapsed());
}
