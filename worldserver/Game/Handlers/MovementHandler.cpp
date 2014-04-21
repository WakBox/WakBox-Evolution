#include "Server/WorldSession.h"

void WorldSession::HandleCharMovement(WorldPacket& packet)
{
    qint32 fromX, fromY;
    qint16 fromZ;
    quint8 stepsCount;

    packet >> fromX >> fromY >> fromZ >> stepsCount;
    quint8 steps[stepsCount];

    //qDebug() << "Movement packet | fromX : " << fromX << " fromY : " << fromY << " fromZ : " << fromZ << " StepsCount : " << stepsCount << " Steps :";

    for (quint8 i = 0; i < stepsCount; ++i)
    {
        quint8 direction;
        packet >> direction;
        steps[i] = (direction >> 5) & 0x7;
    }


    // Todo check coords with map file, collision, etc. ?
    Character* character = GetCharacter();
    if (!character)
        return;

    for (quint8 i = 0; i < stepsCount; ++i)
    {
        switch (steps[i])
        {
        case 0:
            ++fromX;
            --fromY;
            break;
        case 1:
            ++fromX;
            break;
        case 2:
            ++fromX;
            ++fromY;
            break;
        case 3:
            ++fromY;
            break;
        case 4:
            --fromX;
            ++fromY;
            break;
        case 5:
            --fromX;
            break;
        case 6:
            --fromX;
            --fromY;
            break;
        case 7:
            --fromY;
            break;
        default:
            qDebug() << "Direction unknown !";
            break;
        }
    }

    //qDebug () << "New position : " << fromX << " - " << fromY;

    character->SetPosition(fromX, fromY, fromZ);
    character->SetDirection(steps[stepsCount - 1]);
}

void WorldSession::HandleCharDirection(WorldPacket& packet)
{
    quint8 direction;
    packet >> direction;

    Character* character = GetCharacter();
    if (!character)
        return;

    character->SetDirection(direction);

    WorldPacket data(SMSG_CHAR_DIRECTION);
    data << character->GetGuid();
    data << direction;
    SendPacket(data);
}

void WorldSession::HandleCharEmote(WorldPacket& packet)
{
    // We receive an empty packet
    // We send back the current position of the player (x, y) -> 4124
    // And then the emote status -> 4170
}
