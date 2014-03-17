#include "Server/WorldSession.h"

void WorldSession::HandleWorldSelect(WorldPacket& packet)
{
    quint32 worldId;
    packet >> worldId;

    WorldPacket data(SMSG_WORLD_SELECT_RESULT);
    data << worldId;
    data << quint8(0); // 0 = success, 1 = error
    SendPacket(data);

    SendServerTime();
    SendCharactersList();
}

void WorldSession::SendEnterWorld()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_ENTER_WORLD);
    data << quint64(character->GetGuid());
    data.StartBlock<quint16>();
    {
        data << quint8(15);
        data << quint32(0); // Nation Id
        data << quint64(0); // Ranks
        data << quint64(0); // Jobs
        data << quint64(0); // Votedate
        data << quint8(0); // Government Opionion => TODO : aWj.java
        data << quint8(0); // IsCandidate (bool)
        data << quint16(0); // Guild info

        data << quint16(0); // Unk
        data << quint32(9322368); // Unk
        data << quint16(0); // Unk
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}

void WorldSession::HandleInteractiveElement(WorldPacket &packet)
{
    quint64 id;
    quint16 type;

    packet >> id;
    packet >> type;

    qDebug() << "Client ask for interactive element " << id << " , type " << type;

    // Result with opcode 202
}

void WorldSession::SendUpdateObject()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_UPDATE_OBJECT);
    data << quint8(0);
    data << quint8(1);

    data << quint8(0);
    data << character->GetGuid();

    data.StartBlock<quint16>();
    {
        data << quint8(7);
        data << character->GetGuid();
        data << quint8(0);
        data << GetAccountInfos().id;
        data << quint8(0);
        data.WriteString(character->GetName());

        data << character->GetBreed();
        data << character->GetPositionX();
        data << character->GetPositionY();
        data << character->GetPositionZ();
        data << character->GetInstanceId();
        data << character->GetDirection();

        // *** Skin
        data << character->GetGender();
        data << character->GetSkinColor();
        data << character->GetHairColor();
        data << character->GetPupilColor();
        data << character->GetSkinColorFactor();
        data << character->GetHairColorFactor();
        data << character->GetClothIndex();
        data << character->GetFaceIndex();
        data << qint16(-1); // Titles
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}
