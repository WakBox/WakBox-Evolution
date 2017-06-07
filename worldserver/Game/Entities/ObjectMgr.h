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

typedef QHash<qint64, CreatureData> CreatureDataHash;
typedef QHash<quint32, QString> InteractiveElementsHash;

class Character;

class ObjectMgr : public Singleton<ObjectMgr>
{
public:
    ObjectMgr();
    ~ObjectMgr();

    void SetHighestGuids();
    quint32 GenerateGuid(GuidType type);

    void LoadCreatures();
    void LoadInteractiveElements();
    const QString GetInteractiveElementScriptNameById(quint32 id);

private:
    quint32 m_highCharacterGuid;
    CreatureDataHash m_creatureData;
    InteractiveElementsHash m_interactiveElements;
};

#define sObjectMgr ObjectMgr::Instance()

#endif // OBJECTMGR_H
