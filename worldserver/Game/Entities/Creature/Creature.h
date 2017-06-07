#ifndef CREATURE_H
#define CREATURE_H

#include "Entities/Unit/Unit.h"

struct CreatureData
{
    quint32 id;
    quint16 level;
    qint32 position_x;
    qint32 position_y;
    qint16 position_z;
    quint8 direction;
    qint32 instance_id;
    quint32 group_id;
};

class Creature : public Unit
{
public:
    Creature();
    ~Creature();

protected:

};

#endif // CREATURE_H
