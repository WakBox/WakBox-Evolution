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

typedef QMap<quint32, QString> InteractiveElementsMap;

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

    void LoadInteractiveElements();
    const QString &GetInteractiveElementScriptNameById(quint32 id);

private:
    quint32 m_highCharacterGuid;
    InteractiveElementsMap m_interactiveElements;
};

#endif // OBJECTMGR_H
