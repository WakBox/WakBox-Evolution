#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"
#include "Miscellaneous/SharedDefines.h"
#include "Utils/Util.h"

void WorldSession::SendAdditionalSlotsUpdate()
{
    WorldPacket data(SMSG_ADDITIONAL_CHARACTER_SLOTS_UPDATE);
    data << (quint8) 0;
    SendPacket(data);
}

void WorldSession::SendCharactersList()
{
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTERS_BY_ACCOUNT_ID, QVariantList() << GetAccountInfos().id);

    WorldPacket data(SMSG_CHAR_LIST);
    data << (quint8) result.size();

    while (result.next())
    {
        // Must check packet struct
        data.StartBlock<quint16>();
        {
            // Character Part ID
            data << (quint8) CHARACTER_SERIALIZATION_TYPE_FOR_CHARACTER_LIST;

            // ID
            data << quint64(result.value("guid").toULongLong());

            // IDENTITY
            data << (quint8) CHARACTER_TYPE_ID_PLAYER; // typeId (player = 0, non-player = 1)
            data << quint64(result.value("account_id").toULongLong());

            // NAME
            data.WriteString(result.value("name").toString(), STRING_SIZE_2);

            // BREED
            data << quint16(result.value("breed").toUInt());

            // APPEARANCE
            data << quint8(result.value("gender").toUInt());
            data << quint8(result.value("skin_color").toUInt());
            data << quint8(result.value("hair_color").toUInt());
            data << quint8(result.value("pupil_color").toUInt());
            data << quint8(result.value("skin_color_factor").toUInt());
            data << quint8(result.value("hair_color_factor").toUInt());
            data << quint8(result.value("cloth").toUInt());
            data << quint8(result.value("face").toUInt());
            data << qint16(result.value("title").toUInt());

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
            data << quint64(result.value("xp").toULongLong());

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

        Character* newChar = new Character(this);

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

                SetCharacter(newChar);

                SendSelectCharacterResult(true);
                SendCharacterEnterWorld();
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
    SendCharacterEnterWorldPackets();
}

void WorldSession::SendSelectCharacterResult(bool result)
{
    WorldPacket data(SMSG_CHAR_SELECT);
    data << quint8((result) ? 0 : 1);
    SendPacket(data);
}

void WorldSession::SendCharacterEnterWorldPackets()
{
    // Send packet 3222
    // Send packet 3144
    // Send packet 3146

    // Send packet 20000 nation synchro

    SendCharacterInformation();
    SendCharacterEnterWorld();

    // Send packet 5300 : Long UID list (reserved) ?

    WorldPacket data(SMSG_SEND_CHAR_POSITION);
    data << GetCharacter()->GetPositionX();
    data << GetCharacter()->GetPositionY();
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

    SendCharacterUpdate();
}

void WorldSession::SendCharacterInformation()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_INFORMATION);

    // *** Reserved Character Unique ID
        data << quint16(20);
        for (quint8 i = 0; i < 20; ++i)
            data << quint64(27973262776467742 + i);
    // ********************************

    data.StartBlock<quint32>();
    {
        data << quint8(7); // Char part Id

        // ID
        character->SerializeGuid(data);

        // IDENTITY
        character->SerializeIdentity(data);

        // NAME
        character->SerializeName(data);

        // BREED
        character->SerializeBreed(data);

        // HP
        character->SerializeHP(data);

        // POSITION
        character->SerializePosition(data);

        // APPEARANCE
        character->SerializeAppearance(data);

        // SHORTCUT_INVENTORIES
        character->SerializeShortcutInventories(data);

        // EMOTE_INVENTORY
        character->SerializeEmoteInventory(data);

        // LANDMARK_INVENTORY
        character->SerializeLandmarkInventory(data);

        // DISCOVERED_ITEMS
        character->SerializeDiscoveredItems(data);

        // SPELL_INVENTORY
        character->SerializeSpellInventory(data);

        // INVENTORIES
        character->SerializeInventories(data);

        // EQUIPMENT_INVENTORY
        character->SerializeEquipmentInventory(data);

        // BAGS
        character->SerializeBags(data);

        // BREED_SPECIFIC
        character->SerializeBreedSpecific(data);

        // SKILL_INVENTORY
        character->SerializeSkillInventory(data);

        // CRAFT
        character->SerializeCraft(data);

        // APTITUDE_INVENTORY
        character->SerializeAptitudeInventory(data);

        // RUNNING_EFFECTS
        character->SerializeRunningEffects(data);

        // DIMENSIONAL_BAG_FOR_LOCAL_CLIENT
        character->SerializeDimensionalBagForLocalClient(data);

        // CHALLENGES
        character->SerializeChallenges(data);

        // XP
        character->SerializeXP(data);

        // XP_CHARACTERISTICS
        character->SerializeXPCharacteristics(data);

        // TITLES
        character->SerializeTitles(data);

        // CITIZEN_POINT
        character->SerializeCitizenPoint(data);

        // PASSEPORT_INFO
        character->SerializePasseportInfo(data);

        // SOCIAL_STATES
        character->SerializeSocialStates(data);

        // PET
        character->SerializePet(data);

        // ACHIEVEMENTS
        character->SerializeAchievements(data);

        // ACCOUNT_INFORMATION
        character->SerializeAccountInformation(data);

        // LOCK_TO_CLIENT
        character->SerializeLockToClient(data);

        // DIMENSIONAL_BAG_VIEWS_INVENTORY
        character->SerializeDimensionalBagViewsInventory(data);

        // PERSONAL_EFFECTS
        character->SerializePersonalEffects(data);

        // ANTI_ADDICTION
        character->SerializeAntiAddiction(data);

        // WORLD_PROPERTIES
        character->SerializeWorldProperties(data);

        // VISIBILITY
        character->SerializeVisibility(data);

        // OCCUPATION
        character->SerializeOccupation(data);

        // APTITUDE_BONUS_INVENTORY
        character->SerializeAptitudeBonusInventory(data);
    }
    data.EndBlock<quint32>();

    SendPacket(data);
}

void WorldSession::SendCharacterEnterWorld()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_ENTER_WORLD);

    data.StartBlock<quint16>();
    {
        data << quint8(26); // CharacterPartId

        // ID
        character->SerializeGuid(data);

        // IDENTITY
        character->SerializeIdentity(data);

        // POSITION
        character->SerializePosition(data);
    }
    data.EndBlock<quint16>();

    // serializedProtectors
    data << quint16(0);

    // nbProtectors
    data << quint16(0);

    // serializedProtectorInfos
    data << quint16(0);

    SendPacket(data);
}

void WorldSession::SendCharacterUpdate()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_UPDATE);

    character->SerializeGuid(data);

    data.StartBlock<quint16>();
    {
        // Char part Id
        data << quint8(19);

        character->SerializeNationId(data);

        character->SerializeNationSynchro(data);

        character->SerializeGuildLocalInfo(data);

        character->SerializeNationPvpMoney(data);
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}

void WorldSession::HandleSwitchChar(WorldPacket& /*packet*/)
{
    // Save perso, delete pointer, etc...
    SendCharactersList();
}
