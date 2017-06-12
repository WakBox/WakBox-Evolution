#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "Packets/WorldPacket.h"

enum TypeId
{
    TYPEID_OBJECT              = 0,
    TYPEID_CHARACTER           = 1,
    TYPEID_UNIT                = 2,
    TYPEID_CREATURE            = 3
};

class Unit;
class Character;
class Creature;

class Object
{
public:
    Object();
    ~Object();

    TypeId GetTypeId() { return m_typeId; }

    void SetGuid(quint64 guid) { m_guid = guid; }
    quint64 GetGuid() const { return m_guid; }

    void SetInWorld(bool inWorld = true);
    bool IsInWorld() const { return m_inWorld; }

    Character* ToCharacter() { if (GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Character*>(this); else return nullptr; }
    Creature* ToCreature() { if (GetTypeId() == TYPEID_CREATURE) return reinterpret_cast<Creature*>(this); else return nullptr; }

    // Todo
    //virtual void AddToWorld();
    //virtual void RemoveFromWorld();

protected:
    quint64 m_guid;
    TypeId m_typeId;
    bool m_inWorld;
};

#endif // OBJECT_H
