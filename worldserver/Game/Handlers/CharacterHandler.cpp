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

            // ACTIVE_EQUIPMENT_SHEET
            data << quint8(0); // index

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
                data << quint8(0); // needInitialXp
            }

            // XP
            data << quint64(result.value("xp").toULongLong());

            // CHARACTER_LIST_NATION_ID
            data << quint32(0);

            // GUILD_ID
            data << quint64(0); // GuildId

            // GUILD_BLAZON
            data << quint64(0); // GuildBlazonId

            // INSTANCE_ID
            data << quint16(527); // InstanceId -> todo DB
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
    quint8 unkBool;

    packet >> unk;

    packet >> gender >> skinColor >> hairColor >> pupilColor;
    packet >> skinColorFactor >> hairColorFactor >> cloth >> face;

    packet >> breed;

    name = packet.ReadString();

    packet >> unkBool;

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

                SendCharactersList();
                /*SetCharacter(newChar);

                SendSelectCharacterResult(true);
                SendCharacterEnterWorld();*/
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
    QString name;

    packet >> guid;
    name = packet.ReadBigString(STRING_SIZE_4);

    qDebug() << "Character : " << name << " selected.";

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
    SendModerationRequest();

    SendFriendList();
    SendIgnoreList();

    // Send packet 5567 ??

    // Send packet 20000 nation synchro
    // Send 8427, 8418, 20002, 20000

    SendCharacterInformation();

    // Send 5200
    SendCharacterEnterWorld();

    // Send packet 5300 : Long UID list (reserved) ?

    WorldPacket data(SMSG_SEND_CHAR_POSITION);
    data << int(0); //GetCharacter()->GetPositionX();
    data << int(1); //GetCharacter()->GetPositionY();
    SendPacket(data);

    /* TODO - next
    //SendUpdateObject();

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

    // Send 4124
    // Send 6230, loads of them?
    // Send 4123

    SendCharacterUpdate();
    */
}

void WorldSession::SendCharacterInformation()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_INFORMATION);
    data.WriteRawBytes(Utils::FromHexString("00 14 00 67 79 BE CA 00 00 35 00 67 79 BE CA 00 00 36 00 67 79 BE CA 00 00 37 00 67 79 BE CA 00 00 38 00 67 79 BE CA 00 00 39 00 67 79 BE CA 00 00 3A 00 67 79 BE CA 00 00 3B 00 67 79 BE CA 00 00 3C 00 67 79 BE CA 00 00 3D 00 67 79 BE CA 00 00 3E 00 67 79 BE CA 00 00 3F 00 67 79 BE CA 00 00 40 00 67 79 BE CA 00 00 41 00 67 79 BE CA 00 00 42 00 67 79 BE CA 00 00 43 00 67 79 BE CA 00 00 44 00 67 79 BE CA 00 00 45 00 67 79 BE CA 00 00 46 00 67 79 BE CA 00 00 47 00 67 79 BE CA 00 00 48 00 00 07 BF 08 00 00 00 01 00 47 51 D1 00 00 00 00 00 04 66 2B 40 00 08 47 72 65 6D 6D 75 72 65 00 08 00 00 00 3C 00 00 00 00 00 00 00 01 00 00 04 2F 07 01 00 00 00 00 00 00 00 00 00 00 00 00 00 02 0E 00 03 02 00 00 FF FF 00 06 00 00 00 00 00 00 00 00 00 00 00 00 01 00 00 01 00 00 00 01 00 00 4E 2F 00 01 1E 00 02 00 00 4B 31 00 00 68 6A 00 00 00 00 00 00 00 00 FF FF FF FF 00 03 01 00 67 79 BE 21 00 01 A3 00 00 12 AC 00 01 00 01 00 67 79 BE 21 00 01 A2 00 00 12 A7 00 01 00 01 00 67 79 BE 21 00 01 A4 00 00 12 B1 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 67 79 BE 21 00 01 9E 00 00 08 7F 00 00 1E 00 00 00 67 79 BE 21 00 01 A1 00 00 0A 2B 01 00 04 00 00 00 00 00 00 19 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00 44 00 00 00 00 00 00 00 00 00 00 00 00 00 04 00 00 00 00 00 00 00 00 00 00 00 00 00 45 00 00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00 00 00 46 00 00 00 00 00 00 00 00 00 00 00 00 00 06 00 00 00 00 00 00 00 00 00 00 00 00 00 47 00 00 00 00 00 00 00 00 00 00 00 00 00 07 00 00 00 00 00 00 00 00 00 00 00 00 00 48 00 00 00 00 00 00 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00 00 00 00 00 00 00 49 00 00 00 00 00 00 00 00 00 00 00 00 00 09 00 00 00 00 00 00 00 00 00 00 00 00 00 4A 00 00 00 00 00 00 00 00 00 00 00 00 00 4B 00 00 00 00 00 00 00 00 00 00 00 00 00 4C 00 00 00 00 00 00 00 00 00 00 00 00 00 4D 00 00 00 00 00 00 00 00 00 00 00 00 00 0E 00 00 00 00 00 00 00 00 00 00 00 00 00 25 00 00 00 00 00 00 00 00 00 00 00 00 00 2A 00 00 00 00 00 00 00 00 00 00 00 00 00 3C 00 00 00 00 00 00 00 00 00 00 00 00 00 3D 00 00 00 00 00 00 00 00 00 00 00 00 00 3E 00 00 00 00 00 00 00 00 00 00 00 06 00 00 00 48 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 49 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4B 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00 02 00 00 00 00 14 7A A9 E2 11 70 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 14 7A A9 E1 11 6B 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 00 47 51 D1 00 08 47 72 65 6D 6D 75 72 65 00 00 00 00 00 00 00 00 09 00 00 00 00 01 00 00 10 A6 00 67 79 BE 21 00 01 A0 FF FF FF FF FF FF FF FF FF FF FF FF 01 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 02 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 03 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 04 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 05 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 06 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 07 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 08 00 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 00 00 01 98 01 00 00 00 00 00 00 01 00 01 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 06 29 00 00 28 00 00 27 00 00 26 00 00 25 00 00 24 00 00 00 06 29 00 00 28 00 00 27 00 00 26 00 00 25 00 00 24 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4A 00 00 00 03 01 00 00 0B 6E 00 00 01 59 D5 A9 A5 30 00 00 00 00 00 00 00 02 00 00 0B 6E 01 01 00 00 01 59 D5 A9 A5 30 00 00 00 00 00 00 00 00 00 00 0B 3F 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 64 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 65 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 59 D6 43 BA 80 00 00 00 00 00 00 00 00 00 16 00 00 01 E0 00 00 01 DF 00 00 01 DE 00 00 01 FB 00 00 01 75 00 00 01 D3 00 00 03 48 00 00 03 47 00 00 03 46 00 00 03 45 00 00 03 44 00 00 03 43 00 00 03 42 00 00 03 41 00 00 01 FE 00 00 01 FD 00 00 01 FC 00 00 01 9A 00 00 01 98 00 00 00 13 00 00 01 96 00 00 01 95 00 09 00 01 6F 10 00 01 6F 0F 00 01 6F 0E 00 01 6F 0D 00 01 6F 0C 00 01 6F 0B 00 01 6F 0A 00 01 6F 08 00 01 6D A8 00 00 00 00 00 00 01 00 00 02 FF FF FF FF 00 0C 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 06 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF 00 00 00 00 00 0C 00 00 12 A7 00 00 12 AC 00 00 12 B1 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 06 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF 00 00 00 01 00 24 0A 04 08 16 10 0B 0A 04 08 27 10 0B 0A 04 08 68 10 0B 0A 04 08 6A 10 0B 0A 04 08 6D 10 0B 0A 04 08 6E 10 14 00 00 00 4F 08 00 12 17 08 00 12 00 18 FF FF FF FF FF FF FF FF FF 01 20 00 28 00 30 00 38 01 1A 32 08 FF FF FF FF FF FF FF FF FF 01 12 00 18 00 20 FF FF FF FF FF FF FF FF FF 01 28 FF FF FF FF FF FF FF FF FF 01 30 FF FF FF FF FF FF FF FF FF 01 38 00 00 00 00 11 12 0F 08 00 12 00 18 FF FF FF FF FF FF FF FF FF 01"));
    SendPacket(data);
    return;

    // *** Reserved Character Unique ID
        data << quint16(20);
        for (quint8 i = 0; i < 20; ++i)
            data << quint64(2797326277646774 + i);
    // ********************************

    data.StartBlock<quint32>();
    {
        data << quint8(8); // Char part Id

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

        // BAGS
        character->SerializeBags(data);

        // PROTO_TEMPORARY_INVENTORY
        character->SerializeProtoTemporaryInventory(data);

        // BREED_SPECIFIC
        character->SerializeBreedSpecific(data);

        // SKILL_INVENTORY
        character->SerializeSkillInventory(data);

        // CRAFT
        character->SerializeCraft(data);

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

        // SPELL_DECK
        character->SerializeSpellDeck(data);

        // DUNGEON_PROGRESSION
        character->SerializeDungeonProgression(data);
    }
    data.EndBlock<quint32>();

    data.WriteRawBytes(Utils::FromHexString("00 4F 08 00 12 17 08 00 12 00 18 FF FF FF FF FF FF FF FF FF 01 20 00 28 00 30 00 38 01 1A 32 08 FF FF FF FF FF FF FF FF FF 01 12 00 18 00 20 FF FF FF FF FF FF FF FF FF 01 28 FF FF FF FF FF FF FF FF FF 01 30 FF FF FF FF FF FF FF FF FF 01 38 00 00 00 00 11 12 0F 08 00 12 00 18 FF FF FF FF FF FF FF FF FF 01"));

    // Send buildSheet.proto
    // Send aptitude.proto
    /*data.StartBlock<quint32>();
    {

    }
    data.EndBlock<quint32>();

    data.StartBlock<quint32>();
    {

    }
    data.EndBlock<quint32>();*/

    SendPacket(data);
}

void WorldSession::SendCharacterEnterWorld()
{
    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_CHARACTER_ENTER_WORLD);
    data.WriteRawBytes(Utils::FromHexString("00 2C 1A 00 00 00 01 00 47 51 D1 00 00 00 00 00 04 66 2B 40 00 00 00 00 00 00 00 01 00 00 04 2F 07 01 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 02 00 00 00 0A 08 00 10 0B 18 01 20 01 28 00"));
    SendPacket(data);
    return;

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
    data.StartBlock<quint16>();
    {
        data << quint16(0); // nbProtectors
    }
    data.EndBlock<quint16>();

    // serializedProtectorInfos
    data.StartBlock<quint16>();
    {
        data << quint16(0); // nbProtectorsInfos
    }
    data.EndBlock<quint16>();

    // Dungeon Statis ProtoBuf?
    data << quint16(10); // Size

    // unk data
    data << quint8(10);
    data << quint8(8);
    data << quint8(0);
    data << quint8(16);
    data << quint8(11);
    data << quint8(24);
    data << quint8(1);
    data << quint8(32);
    data << quint8(1);
    data << quint8(40);
    data << quint8(0);

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
