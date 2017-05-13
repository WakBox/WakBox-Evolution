#include "Server/WorldSession.h"

void WorldSession::HandleCharMovement(WorldPacket& packet)
{
    qint32 fromX, fromY;
    qint16 fromZ;
    quint8 stepsCount;

    packet >> fromX >> fromY >> fromZ >> stepsCount;
    QVector<quint8> steps;

    qDebug() << "Movement packet | fromX : " << fromX << " fromY : " << fromY << " fromZ : " << fromZ << " StepsCount : " << stepsCount;
    qDebug() << "Steps :";

    for (quint8 i = 0; i < stepsCount; ++i)
    {
        quint8 step;
        packet >> step;

        qDebug() << "[" << i << "] Step Byte : " << step;

        quint8 direction = (step >> 5) & 0x7;

        qDebug() << "[" << i << "] Direction: " << direction;

        int heightDiff = step & 0x1F;
        if ((heightDiff & 0x10) != 0x0) {
          heightDiff |= 0xFFFFFFE0;
        }

        fromZ += heightDiff;

        qDebug() << "[" << i << "] heightDiff: " << heightDiff;

        steps.push_back(direction);

        qDebug() << " ";
    }

    // Todo check coords with map file, collision, etc. ?
    // All this pointer check should be done somewhere else / using packet status? => STATUS_IN_WORLD :)
    Character* character = GetCharacter();
    if (!character)
        return;

    for (quint8 i = 0; i < steps.count(); ++i)
    {
        switch (steps.at(i))
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

    qDebug () << "New position : " << fromX << " - " << fromY << " - " << fromZ;

    character->SetPosition(fromX, fromY, fromZ);
    character->SetDirection(steps.last());

    // Todo send to player in the area only
    WorldPacket data(SMSG_UPDATE_POSITION);
    data << character->GetGuid();
    data << character->GetPositionX();
    data << character->GetPositionY();
    data << character->GetPositionZ();
    data << character->GetDirection();
    sWorld->SendGlobalPacket(data, this);
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

void WorldSession::HandleCharEmote(WorldPacket& /*packet*/)
{
    // We receive an empty packet
    // We send back the current position of the player (x, y) -> 4124
    // And then the emote status -> 4170
}
