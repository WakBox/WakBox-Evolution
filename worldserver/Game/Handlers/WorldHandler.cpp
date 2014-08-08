#include "Server/WorldSession.h"

void WorldSession::SendWorldSelectResult()
{
    WorldPacket data(SMSG_WORLD_SELECT_RESULT);
    data << quint8(0); // 0 = success, 1 = error
    SendPacket(data);

    // Send 2078 ?
    SendServerTime();
    // Send 2067 ?
    SendCharactersList();
    // Send 2077 ?
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
        // Char part Id
        data << quint8(15);

        // NATION_ID
        data << quint32(0); // Nation Id

        // NATION_SYNCHRO
        data << quint64(0); // Ranks
        data << quint64(0); // Jobs
        data << quint64(0); // Votedate
        data << quint8(0); // Government Opionion => TODO : aWj.java
        data << quint8(0); // IsCandidate (bool)

        // GUILD_LOCAL_INFO
        data << quint16(0); // Guild info
        data << quint32(66); // havenWorldId
        data << float(0.0f); // moderationBonusLearningFactor
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

    ScriptMgr::Instance()->OnInteractiveElementActive(this->GetCharacter(), id, (InteractiveElementType)type);
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
        data.WriteString(character->GetName(), true);

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

        // PUBLIC_CHARACTERISTICS
        data << quint16(0); // size

        // FIGHT_PROPERTIES
        data << quint8(0); // hasProperties

        // FIGHT
        data << qint32(-1); // currentFightId
        data << quint8(0); // isKo
        data << quint8(0); // isDead
        data << quint8(0); // isSummonned
        data << quint8(0); // isFleeing
        data << qint8(-1); // obstacleId

        data << quint8(0); // hasSummon

        // EQUIPMENT_APPEARANCE
        data << quint16(0); // Views size

        // RUNNING_EFFECTS
        data << quint8(0); // hasInFightData
        data << quint8(0); // hasOutFightData

        // CURRENT_MOVEMENT_PATH
        data << quint8(0); // hasCurrentPath

        // WORLD_PROPERTIES
        data << quint8(0); // hasProperties

        // GROUP
        data << quint64(0); // partyId

        // TEMPLATE
        data << quint16(0); // sightRadius
        data << quint16(0); // aggroRadius

        // COLLECT
        data << quint16(0); // unavailableActions size

        // OCCUPATION
        data << quint8(0); // hasOccupation

        // XP
        data << character->GetXP();

        // XP_CHARACTERISTICS
        data << character->GetXPFreePoints();
        data << quint16(0); // xpBonusPoints size
        data << quint16(0); // characteristicBonusPoints size

        data << character->GetXPGauge(); // Should be named WakfuGauge...

        // CITIZEN_POINT
        data << quint16(0); // nationCitizenScores
        data << quint16(0); // offendedNations

        // GUILD_REMOTE_INFO
        data << character->GetGuildId();
        data << quint64(0); // Blazon
        data << quint16(0); // Level
        data << quint16(0); // GuildName

        // NATION_ID
        data << quint32(0); // NationId

        // NATION_SYNCHRO
        data << quint64(0); // rank
        data << quint64(0); // jobs
        data << quint64(0); // vote
        data << quint8(0); // governmentOpinion
        data << quint8(0); // isCandidate

        // SOCIAL_STATES
        data << quint8(0); // afkState
        data << quint8(0); // dndState

        // PET
        data << quint8(0); // hasPet

        // ACCOUNT_INFORMATION_REMOTE
        data << quint32(0); // subscriptionLevel
        data << quint16(0); // additionalRights size

        // COMPANION_CONTROLLER_ID
        data << quint64(0); // controllerId
        data << quint64(0); // companionId
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}
