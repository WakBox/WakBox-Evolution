#include "Creature.h"

Creature::Creature() : Unit()
{
    m_typeId = TYPEID_CREATURE;
}

Creature::~Creature()
{

}

void Creature::SetData(CreatureData const& data)
{
    SetBreed(data.id);
    SetLevel(data.level);
    SetPosition(data.position_x, data.position_y, data.position_z);
    SetDirection(data.direction);
    SetInstanceId(data.instance_id);
    //quint32 group_id;
}
