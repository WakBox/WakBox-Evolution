#include "ObjectMgr.h"
#include "Configuration/ConfigMgr.h"
#include "Logs/Log.h"
#include "Define.h"

template<> ObjectMgr*  Singleton<ObjectMgr>::m_instance = 0;

ObjectMgr::ObjectMgr()
{
    m_highCharacterGuid = 0;
}

ObjectMgr::~ObjectMgr() {}

void ObjectMgr::SetHighestGuids()
{
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_MAX_GUID);
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

void ObjectMgr::LoadInteractiveElements()
{
    QTime t;
    t.start();

    QSqlQuery result = Database::World()->Query(SELECT_INTERACTIVE_ELEMENTS);
    QSqlRecord rows = result.record();

    while (result.next())
        m_interactiveElements[(quint32)result.value(rows.indexOf("interactive_element_id")).toUInt()] = result.value(rows.indexOf("script_name")).toString();

    Log::Write(LOG_TYPE_NORMAL, ">> Loaded %u interactive elements in %u ms.", m_interactiveElements.count(), t.elapsed());
}

const QString &ObjectMgr::GetInteractiveElementScriptNameById(quint32 id)
{
    return m_interactiveElements.value(id, QString());
}
