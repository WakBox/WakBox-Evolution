#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"
#include "Maps/MapMgr.h"
#include "Miscellaneous/SharedDefines.h"
#include "Utils/Util.h"
#include "Proto/equipment.pb.h"
#include "Proto/dimensionalBag.pb.h"
#include "Proto/dungeon_progression.pb.h"
#include "Proto/buildSheet.pb.h"
#include "Proto/aptitude.pb.h"
#include "Proto/dungeon.pb.h"

void WorldSession::SendAdditionalSlotsUpdate()
{
    WorldPacket data(SMSG_ADDITIONAL_CHARACTER_SLOTS_UPDATE);
    data << (quint8) 0;
    SendPacket(data);
}

void WorldSession::SendCharactersList()
{
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTERS_BY_ACCOUNT_ID, QVariantList() << GetAccountInfos().id);
    WakfuProto::ProtoEquipmentAccount protoEquipmentAccount;

    WorldPacket data(SMSG_CHAR_LIST);

    data << (quint8) result.size();

    while (result.next())
    {
        // ProtoEquipmentAccount
        WakfuProto::ProtoEquipmentSet* protoEquipmentSet = protoEquipmentAccount.add_sets();
        WakfuProto::ProtoEquipmentSheet* equipmentSheets = protoEquipmentSet->add_sheets();

        std::string emptyString = "";
        equipmentSheets->set_index(0);
        equipmentSheets->set_name(emptyString);
        equipmentSheets->set_level(-1);

        protoEquipmentSet->set_characterid(result.value("guid").toULongLong());

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

    WorldPacket data4(5255);
    QByteArray protoEquipmentSetBin;
    protoEquipmentSetBin.resize(protoEquipmentAccount.ByteSize());
    protoEquipmentAccount.SerializeToArray(protoEquipmentSetBin.data(), protoEquipmentSetBin.size());

    data4.StartBlock<quint32>();
    {
        data4.WriteRawBytes(protoEquipmentSetBin);
    }
    data4.EndBlock<quint32>();

    SendPacket(data4);

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
            // I think tutorial mode is different now?
            //if (breed == CHARACTER_BREED_TUTORIAL)
            //{
                newChar->SetPosition(40, -1, 4);
                newChar->SetDirection(7);
                newChar->SetInstanceId(527);
            //}

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
        else { /*error code?*/ }
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

    // Send packet 20002
    // Send packet 20000

    // Send 5567

    // Send packet 20000

    // Send packet 8427
    // Send packet 8418

    SendCharacterInformation();

    // Send 5200

    // Need to be updated!
    SendCharacterEnterWorld();

    // Send packet 5300 : Long UID list (reserved) ?

    WorldPacket data(SMSG_SEND_CHAR_POSITION);
    data << qint32(40); //GetCharacter()->GetPositionX();
    data << qint32(-1); //GetCharacter()->GetPositionY();
    SendPacket(data);

    // Send 4202 - multiple times

    // todo: move it?
    Map* map = sMapMgr->CreateMap(GetCharacter()->GetInstanceId());
    if (!map)
    {
        Log::Write(LOG_TYPE_NORMAL, "Error while creating map %i!", GetCharacter()->GetInstanceId());
        return;
    }

    map->AddCharacterToMap(GetCharacter());

    // 200
    /*WorldPacket data2(SMSG_INTERACTIVE_ELEMENT_SPAWN);

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

    // Send 204
    // Send 8006
    // Send 4124
    // Send 9504
    // Send 11214
    // Send 9301
    // Send 12600
    // Send 6320, loads of them?
    // Send 8427
    // Send 4123
    // Send 5567
    // etc.

    SendCharacterUpdate();
    */
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

        //GUILD_BLAZON
        character->SerializeGuildBlazon(data);

        //GUILD_ID
        character->SerializeGuildId(data);

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

        // Send dimensionalBag.proto

        WakfuProto::ProtoDimensionalBagCraftFee protoBagCraftFee;

        WakfuProto::ProtoDimensionalBagCategoryFee* cat1 = protoBagCraftFee.add_categoryfee();
        cat1->set_categoryindex(0);
        cat1->set_equipmentcraftfee(0);
        cat1->set_componentcraftfee(0);

        WakfuProto::ProtoDimensionalBagCategoryFee* cat2 = protoBagCraftFee.add_categoryfee();
        cat2->set_categoryindex(1);
        cat2->set_equipmentcraftfee(0);
        cat2->set_componentcraftfee(0);

        WakfuProto::ProtoDimensionalBagCategoryFee* cat3 = protoBagCraftFee.add_categoryfee();
        cat3->set_categoryindex(2);
        cat3->set_equipmentcraftfee(0);
        cat3->set_componentcraftfee(0);

        protoBagCraftFee.set_isfreeforfriends(0);
        protoBagCraftFee.set_isfreeforguild(0);

        data.StartBlock<quint16>();
        {
            QByteArray protoBagCraftFeeBin;
            protoBagCraftFeeBin.resize(protoBagCraftFee.ByteSize());
            protoBagCraftFee.SerializeToArray(protoBagCraftFeeBin.data(), protoBagCraftFeeBin.size());

            data.WriteRawBytes(protoBagCraftFeeBin);
        }
        data.EndBlock<quint16>();

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

        // Send dungeon_progression.proto
        WakfuProto::ProtoDungeonProgression protoDungeonProgress;

        /*WakfuProto::ProtoDungeonEntry* entry1 = protoDungeonProgress.add_map();
        entry1->set_index(22);
        entry1->set_difficulty(11);

        WakfuProto::ProtoDungeonEntry* entry2 = protoDungeonProgress.add_map();
        entry2->set_index(39);
        entry2->set_difficulty(11);

        WakfuProto::ProtoDungeonEntry* entry3 = protoDungeonProgress.add_map();
        entry3->set_index(104);
        entry3->set_difficulty(11);

        WakfuProto::ProtoDungeonEntry* entry4 = protoDungeonProgress.add_map();
        entry4->set_index(106);
        entry4->set_difficulty(11);

        WakfuProto::ProtoDungeonEntry* entry5 = protoDungeonProgress.add_map();
        entry5->set_index(109);
        entry5->set_difficulty(11);

        WakfuProto::ProtoDungeonEntry* entry6 = protoDungeonProgress.add_map();
        entry6->set_index(110);
        entry6->set_difficulty(20);*/

        data.StartBlock<quint16>();
        {
            QByteArray protoDungeonProgressBin;
            protoDungeonProgressBin.resize(protoDungeonProgress.ByteSize());
            protoDungeonProgress.SerializeToArray(protoDungeonProgressBin.data(), protoDungeonProgressBin.size());

            data.WriteRawBytes(protoDungeonProgressBin);
        }
        data.EndBlock<quint16>();
    }
    data.EndBlock<quint32>();

    data.StartBlock<quint32>();
    {
        // Send buildSheet.proto

        WakfuProto::ProtoBuildSheetSet buildSheetSet;
        buildSheetSet.set_activesheetindex(0);

        WakfuProto::ProtoBuildSheet* sheet1 = buildSheetSet.add_buildsheets();
        std::string emptyString = "";

        sheet1->set_index(0);
        sheet1->set_name(emptyString);
        sheet1->set_level(-1);
        sheet1->set_spelldeckindex(0);
        sheet1->set_aptitudesheetindex(0);
        sheet1->set_equipmentsheetindex(0);
        sheet1->set_iconindex(1);

        WakfuProto::ProtoBuildSheet* autoSheet = new WakfuProto::ProtoBuildSheet();
        autoSheet->set_index(-1);
        autoSheet->set_name(emptyString);
        autoSheet->set_level(0);
        autoSheet->set_spelldeckindex(-1);
        autoSheet->set_aptitudesheetindex(-1);
        autoSheet->set_equipmentsheetindex(-1);
        autoSheet->set_iconindex(0);
        buildSheetSet.set_allocated_automaticsheet(autoSheet);

        QByteArray protoBuildSheetBin;
        protoBuildSheetBin.resize(buildSheetSet.ByteSize());
        buildSheetSet.SerializeToArray(protoBuildSheetBin.data(), protoBuildSheetBin.size());

        data.WriteRawBytes(protoBuildSheetBin);
    }
    data.EndBlock<quint32>();

    data.StartBlock<quint32>();
    {
        // Send aptitude.proto

        WakfuProto::SheetSet sheetSet;
        WakfuProto::Sheet* sheet = sheetSet.add_sheets();
        std::string emptyString = "";

        sheet->set_index(0);
        sheet->set_name(emptyString);
        sheet->set_level(-1);

        QByteArray protoSheetSetBin;
        protoSheetSetBin.resize(sheetSet.ByteSize());
        sheetSet.SerializeToArray(protoSheetSetBin.data(), protoSheetSetBin.size());

        data.WriteRawBytes(protoSheetSetBin);
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
        data << quint8(26);

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

    // Send dungeon.proto
    data.StartBlock<quint16>();
    {
        WakfuProto::ProtoDungeon protoDungeon;
        protoDungeon.set_maxlevel(0);
        protoDungeon.set_difficultylevel(11);
        protoDungeon.set_isdifficultyavailable(true);
        protoDungeon.set_canincreasedifficulty(true);
        protoDungeon.set_isfightinprogress(false);
        protoDungeon.set_iscompetitivecancelled(false);

        QByteArray protoDungeonBin;
        protoDungeonBin.resize(protoDungeon.ByteSize());
        protoDungeon.SerializeToArray(protoDungeonBin.data(), protoDungeonBin.size());

        data.WriteRawBytes(protoDungeonBin);
    }
    data.EndBlock<quint16>();

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
