#ifndef MAP_H
#define MAP_H

#include <QtCore>

#include "Server/WorldSession.h"
#include "Entities/Object/Object.h"

class Character;

typedef QHash<qint16/*partitionId*/, QList<Unit*>> MapObjectList;

class Map
{
public:
    Map(qint16 id);
    ~Map();

    qint16 GetId() { return m_id; }
    QList<Unit*> const& GetPartitionObjectList(qint16 partition) { return m_mapObjects[partition]; }

    void Load();
    void AddCharacterToMap(Character* character);

    void SendPacket(WorldPacket& data, WorldSession* self = nullptr);

private:
    qint16 m_id;

    MapObjectList m_mapObjects;
};

#endif // MAP_H
