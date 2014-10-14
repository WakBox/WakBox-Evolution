#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"
#include "Miscellaneous/SharedDefines.h"
#include "Utils/Util.h"

void WorldSession::SendCharactersList()
{
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTERS_BY_ACCOUNT_ID, QVariantList() << GetAccountInfos().id);

    WorldPacket data(SMSG_CHAR_LIST);
    data << quint8(result.size());

    while (result.next())
    {
        QSqlRecord fields = result.record();

        // Must check packet struct
        data.StartBlock<quint16>();
        {
            // Character Part ID
            data << quint8(4);

            // ID
            data << quint64(result.value(fields.indexOf("guid")).toULongLong());

            // IDENTITY
            data << quint8(0); // idType ?
            data << quint64(result.value(fields.indexOf("account_id")).toULongLong());

            // NAME
            data.WriteString(result.value(fields.indexOf("name")).toString(), true);

            // BREED
            data << quint16(result.value(fields.indexOf("breed")).toUInt());

            // APPEARANCE
            data << quint8(result.value(fields.indexOf("gender")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color")).toUInt());
            data << quint8(result.value(fields.indexOf("pupil_color")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("cloth")).toUInt());
            data << quint8(result.value(fields.indexOf("face")).toUInt());
            data << qint16(result.value(fields.indexOf("title")).toUInt());

            // EQUIPMENT_APPEARANCE
            data << quint8(0); // size

            // CREATION_DATA
            data << quint8(1); // hasCreationData
            {
                data << quint8(0); // isNewChar
                data << quint8(0); // needsRecustom
                data << quint16(0); // recustomValue
            }

            // XP
            data << quint64(result.value(fields.indexOf("xp")).toULongLong());

            // CHARACTER_LIST_NATION_ID
            data << quint32(0);
        }
        data.EndBlock<quint16>();
    }

    SendPacket(data);
}

void WorldSession::HandleLeaveCharSelect(WorldPacket& /*packet*/)
{
    WorldPacket data(SMSG_LEAVE_CHAR_SELECT);
    SendPacket(data);
}

void WorldSession::HandleCharDelete(WorldPacket& packet)
{
    quint64 guid;
    packet >> guid;

    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTER_BY_GUID, QVariantList() << guid);
    quint8 success = 0;

    if (result.first())
    {
        if (result.value(result.record().indexOf("account_id")) == GetAccountInfos().id)
        {
            sCharDatabase->Query(DELETE_CHARACTER_BY_GUID, QVariantList() << guid);
            success = 1;
        }
    }

    WorldPacket data(SMSG_CHAR_DELETE);
    data << guid;
    data << success;
    SendPacket(data);
}

void WorldSession::HandleCharCreate(WorldPacket& packet)
{
    quint64 unk;
    quint8 gender, skinColor, hairColor, pupilColor;
    quint8 skinColorFactor, hairColorFactor, cloth, face;
    quint16 breed;
    QString name;

    packet >> unk;

    packet >> gender >> skinColor >> hairColor >> pupilColor;
    packet >> skinColorFactor >> hairColorFactor >> cloth >> face;

    packet >> breed;

    name = packet.ReadString();

    WorldPacket data(SMSG_CHAR_CREATE);
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTER_BY_NAME, QVariantList() << name);

    if (!result.first())
    {
        // TODO
        // Check max char by account

        sCharacterCreateInfos charCreateInfos(name, breed, gender, skinColor, hairColor, pupilColor,
                                              skinColorFactor, hairColorFactor, cloth, face);

        QScopedPointer<Character> newChar(new Character(this));

        if(newChar->Create(ObjectMgr::Instance()->GenerateGuid(GUIDTYPE_CHARACTER), charCreateInfos))
        {
            if (breed == CHARACTER_BREED_TUTORIAL)
            {
                newChar->SetPosition(0, 0, 0);
                newChar->SetDirection(7);
                newChar->SetInstanceId(621);
            }

            if (newChar->SaveToDB(true))
            {
                data << (quint8)CHARACTER_CREATION_RESULT_SUCCESS;
                SendPacket(data);

                // Auto-connect in world => TODO
                //SendSelectCharacterResult(true);
                return;
            }
            else
                data << (quint8)CHARACTER_CREATION_RESULT_FAILED;
        }
    }
    else
        data << (quint8)CHARACTER_CREATION_RESULT_NAME_EXISTS;

    SendPacket(data);
}

void WorldSession::HandleCharSelect(WorldPacket& packet)
{
    quint64 guid;
    packet >> guid;

    // Check if characters isn't already loaded or in loading.
    /*
    if (PlayerLoading() || GetPlayer() != NULL)
    {
        TC_LOG_ERROR(LOG_FILTER_NETWORKIO, "Player tries to login again, AccountId = %d", GetAccountId());
        return;
    }

    m_playerLoading = true;
    */

    // Is this character owned by this account ?

    Character* character = new Character(this);
    if (!character->LoadFromDB(guid))
    {
        delete character;
        // m_playerLoading = false;
        return;
    }

    SendSelectCharacterResult(true);

    // Send packet 20000 nation synchro ?

    SendCharacterStatsEnterWorld();
    SendCharacterPosition();

    // Send packet 5300 ? Long UID list (reserved) ?

    WorldPacket data(SMSG_SEND_CHAR_POSITION);
    data << character->GetPositionX();
    data << character->GetPositionY();
    SendPacket(data);

    SendUpdateObject();

    WorldPacket data2(SMSG_INTERACTIVE_ELEMENT_SPAWN);

    data2 << quint16(1); // loop size
    data2 << quint64(20114); // Instance ElementId

    // Buffer size
    data2.StartBlock<quint16>();
    {
        data2 << quint8(1); // BlockCount

        data2 << quint8(2); // blockId
        data2 << quint32(6); // offset

        data2 << quint8(2); // BlockId

        data2 << quint16(1); // ?
        data2 << quint8(1); // isVisible
        data2 << quint8(1); // isUsable
        data2 << quint8(0); // ?
        data2 << quint8(0); // ?
        data2 << quint8(0); // ?
        data2 << quint32(0); // ?
    }
    data2.EndBlock<quint16>();

    SendPacket(data2);

    SendEnterWorld();
}

void WorldSession::SendSelectCharacterResult(bool result)
{
    WorldPacket data(SMSG_CHAR_SELECT);
    data << quint8((result) ? 0 : 1);
    SendPacket(data);
}

void WorldSession::SendCharacterStatsEnterWorld()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_STATS_ENTER_WORLD);

    // *** Reserved Character Unique ID
        data << quint16(20);
        for (quint8 i = 0; i < 20; ++i)
            data << quint64(27973262776467742 + i);
    // ********************************

    data.StartBlock<quint32>();
    {
        data << quint8(6); // Char part Id

        // ID
        data << character->GetGuid();

        // IDENTITY
        data << quint8(0); // idType
        data << GetAccountInfos().id;

        // NAME
        data.WriteString(character->GetName(), true);

        // BREED
        data << character->GetBreed();

        // HP
        data << character->GetHealth();

        // POSITION
        data << character->GetPositionX();
        data << character->GetPositionY();
        data << character->GetPositionZ();
        data << character->GetInstanceId();
        data << character->GetDirection();

        // APPEARANCE
        data << character->GetGender();
        data << character->GetSkinColor();
        data << character->GetHairColor();
        data << character->GetPupilColor();
        data << character->GetSkinColorFactor();
        data << character->GetHairColorFactor();
        data << character->GetClothIndex();
        data << character->GetFaceIndex();
        data << qint16(-1);

        // SHORTCUT_INVENTORIES
        data << quint16(0);

        // EMOTE_INVENTORY
        data << quint16(1); // Size
        data << quint32(20015); // EmoteId

        // LANDMARK_INVENTORY
        data << quint16(1); // Size
        data << quint8(30); // LandmarkId

        // DISCOVERED_ITEMS
        data << quint16(0); // ZaapsCount
        data << quint16(0); // dragosCount
        data << quint16(0); // boatscount
        data << quint16(0); // cannonCount
        data << quint16(0); // phoenixCount
        data << qint32(-1); // selectedPhoenix

        // SPELL_INVENTORY
        data << quint16(0); // spellInventoryVersion
        data << quint32(0); // lockedSpellId
        data << quint16(0); // Spell size
        data << quint8(0); // needSpellRestat

        // INVENTORIES
        data << quint16(0); // questInventory size
        data << quint16(0); // temporaryInventory size
        data << quint16(0); // cosmeticsInventory size
        data << quint16(0); // petCosmeticsInventory size

        // EQUIPMENT_INVENTORY
        data << quint16(0); // Count

        // BAGS
        data << quint16(0); // Bags count

        // BREED_SPECIFIC
        data << quint8(0); // hasOsaSpecific

        // SKILL_INVENTORY
        data << quint16(0); // SkillInventory size

        // CRAFT
        data << quint16(0); // Craft count

        // APTITUDE_INVENTORY
        data << quint16(0); // Count
        data << quint16(0); // Count

        data << quint16(21); // Version

        // RUNNING_EFFECTS
        data << quint8(0); // hasInFightData
        data << quint8(0); // hasOutFightData

        // DIMENSIONAL_BAG_FOR_LOCAL_CLIENT
        data << character->GetGuid();
        data.WriteString(character->GetName(), true);
        data << character->GetGuildId();
        data << quint8(0); // Rooms count

        data << quint32(408); // CustomViewModelId
        data << quint8(0); // HasWallet
        data << quint8(0); // dimensionalBagLocked

        data << quint16(0); // groupeEntriesSize
        data << quint16(0); // IndividualEntriesSize

        // CHALLENGES
        data << quint8(0); // hasCurrentScenarii
        data << quint8(0); // hasCurrentChallengeInfo
        data << quint16(0); // pastScenarii

        // XP
        data << character->GetXP();

        // XP_CHARACTERISTICS
        data << character->GetXPFreePoints();
        data << quint16(0); // xpBonusPoints size
        data << quint16(0); // m_characteristicBonusPoints size
        data << character->GetXPGauge();

        // TITLES
        data << quint16(0); // availableTitlesCount

        // CITIZEN_POINT
        data << quint16(0); // nationCitizenScoresSize
        data << quint16(0); // offendedNationsSize

        // PASSEPORT_INFO
        data << quint8(0); // isPassportActive

        // SOCIAL_STATES
        data << quint8(0); // afkState
        data << quint8(0); // dndstate

        // PET
        data << quint8(0); // HasPet

        // ACHIEVEMENTS
        data << quint16(0); // Size

        // ACCOUNT_INFORMATION
        data << quint16(76); // adminRights size
        for (quint8 i = 0; i <= 75; ++i)
            data << quint32(0); // adminRight

        data << quint32(0); // subscriptionLevel
        data << quint32(0); // forcedSubscriptionLevel
        data << quint32(0); // antiAddictionLevel
        data << quint64(0); // sessionStartTime
        data << quint16(0); // additionalRights size

        // LOCK_TO_CLIENT
        data << quint16(0); // Locks size

        // DIMENSIONAL_BAG_VIEWS_INVENTORY
        data << quint16(0); // Views Size

        // PERSONAL_EFFECTS
        data << quint16(0); // guildEffects size
        data << quint16(0); // havenWorldEffects size
        data << quint16(0); // antiAddictionEffects size

        // ANTI_ADDICTION
        data << quint8(0); // hasAddictionData

        // WORLD_PROPERTIES
        data << quint8(0); // hasProperties

        // VISIBILITY
        data << quint8(1); // Visible
    }
    data.EndBlock<quint32>();

    SendPacket(data);
}

void WorldSession::SendCharacterPosition()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_SEND_CHARACTER_POSITION);

    data.StartBlock<quint16>();
    {
        data << quint8(22); // CharacterPartId

        // ID
        data << character->GetGuid();

        // IDENTITY
        data << quint8(0); // idType
        data << GetAccountInfos().id;

        // POSITION
        data << character->GetPositionX();
        data << character->GetPositionY();
        data << character->GetPositionZ();
        data << character->GetInstanceId();
        data << character->GetDirection();
    }
    data.EndBlock<quint16>();

    // TODO check packet 4100
    data << quint16(0); // Protectors size
    // TODO : bnY.java
    data << quint16(0); // Size of something else ?
    data << quint16(0);

    SendPacket(data);
}

void WorldSession::HandleSwitchChar(WorldPacket& /*packet*/)
{
    // Save perso, delete pointer, etc...
    SendCharactersList();
}
