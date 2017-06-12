#include "Unit.h"

void Unit::SerializeGuid(WorldPacket& data)
{
    data << GetGuid();
}

void Unit::SerializeIdentity(WorldPacket& data)
{
    data << quint8(1); // idType
    data << qint64(-1);
}

void Unit::SerializeName(WorldPacket& data)
{
    data.WriteString(GetName(), STRING_SIZE_2);
}

void Unit::SerializeBreed(WorldPacket& data)
{
    data << GetBreed();
}

void Unit::SerializePosition(WorldPacket& data)
{
    data << GetPositionX();
    data << GetPositionY();
    data << GetPositionZ();
    data << GetInstanceId();
    data << GetDirection();

    // dimBagPosition
    data << (quint8) 1;
    {
        data << quint32(0); //x
        data << quint32(0); //y
        data << quint16(0); //z
        data << quint16(0); //instanceid
    }
}

void Unit::SerializeWorldProperties(WorldPacket& data)
{
    data << quint8(0); // hasProperties
}

void Unit::SerializePublicCharacteristics(WorldPacket& data)
{
    data << quint16(0); // size
}

void Unit::SerializeFightProperties(WorldPacket& data)
{
    data << quint8(0); // hasProperties
}

void Unit::SerializeFight(WorldPacket& data)
{
    data << qint32(-1); // currentFightId
    data << quint8(0); // isKo
    data << quint8(0); // isDead
    data << quint8(0); // isSummoned
    data << quint8(0); // isFleeing
    data << qint8(-1); // obstacleId

    data << quint8(0); // hasSUMMONDATA
}

void Unit::SerializeCurrentMovementPath(WorldPacket& data)
{
    data << quint8(0); // hasCurrentPath
}
