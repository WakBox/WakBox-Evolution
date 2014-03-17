#include "ObjectMgr.h"
#include "Configuration/ConfigMgr.h"

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
