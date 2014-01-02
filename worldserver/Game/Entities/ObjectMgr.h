#ifndef OBJECTMGR_H
#define OBJECTMGR_H

#include <QtCore>
#include "Databases/Database.h"
#include "Utils/Singleton.h"

enum GuidType
{
    GUIDTYPE_NONE      = 0,
    GUIDTYPE_CHARACTER = 1
};

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

private:
    quint32 m_highCharacterGuid;
};

#endif // OBJECTMGR_H
