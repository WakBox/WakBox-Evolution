#include "Creature.h"

void Creature::SerializeAppearance(WorldPacket& data)
{
    data << quint8(1);
}

void Creature::SerializeGroup(WorldPacket& data)
{
    data << qint64(-1);
    data << quint16(0);
}

void Creature::SerializeTemplate(WorldPacket& data)
{
    data << qint16(-1);
    data << qint16(-1);
}

void Creature::SerializeCollect(WorldPacket& data)
{
    data << quint16(0);
}

void Creature::SerializeCompanionControllerId(WorldPacket& data)
{
    data << quint64(0);
    data << quint64(0);
}
