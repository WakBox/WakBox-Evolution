#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"
#include "Miscellaneous/SharedDefines.h"
#include "Utils/Util.h"

void WorldSession::SendCharactersList()
{
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTERS_BY_ACCOUNT_ID, QVariantList() << GetAccountInfos().id);

    WorldPacket data(SMSG_CHAR_LIST);
    data << quint8(result.size());

    while (result.next())
    {
        QSqlRecord fields = result.record();

        // Must check packet struct
        data.StartBlock<quint16>();
        {
            // Block type
            data << quint8(4);
            data << quint64(result.value(fields.indexOf("guid")).toULongLong());

            data << quint8(0); // idType ?
            data << quint64(result.value(fields.indexOf("account_id")).toULongLong());

            data.WriteString(result.value(fields.indexOf("name")).toString(), true);
            data << quint16(result.value(fields.indexOf("breed")).toUInt());

            data << quint8(result.value(fields.indexOf("gender")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color")).toUInt());
            data << quint8(result.value(fields.indexOf("pupil_color")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("cloth")).toUInt());
            data << quint8(result.value(fields.indexOf("face")).toUInt());
            data << qint16(result.value(fields.indexOf("title")).toUInt());

            //Stuff
            data << quint8(0); // Size

            data << quint8(1); // creation data
            {
                data << quint8(0); // isNewChar
                data << quint8(0); // needsRecustom
            }

            // XP
            data << quint16(0); // unk (freepoints ??)
            data << quint64(result.value(fields.indexOf("xp")).toULongLong());

            // Nation
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

    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_BY_GUID, QVariantList() << guid);
    quint8 success = 0;

    if (result.first())
    {
        if (result.value(result.record().indexOf("account_id")) == GetAccountInfos().id)
        {
            Database::Char()->Query(DELETE_CHARACTER_BY_GUID, QVariantList() << guid);
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
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_BY_NAME, QVariantList() << name);

    if (!result.first())
    {
        // TODO
        // Check max char by account

        sCharacterCreateInfos charCreateInfos(name, breed, gender, skinColor, hairColor, pupilColor,
                                              skinColorFactor, hairColorFactor, cloth, face);

        QScopedPointer<Character> newChar(new Character(this));

        if(newChar->Create(ObjectMgr::Instance()->GenerateGuid(GUIDTYPE_CHARACTER), charCreateInfos))
        {
            if (breed = CHARACTER_BREED_TUTORIAL)
            {
                newChar->SetPosition(0, 0, 0);
                newChar->SetDirection(7);
                newChar->SetInstanceId(621);
            }

            newChar->SaveToDB(true);

            data << quint8(0);
            SendPacket(data);

            SendSelectCharacterResult(true);
            return;
        }
    }

    data << quint8(10);
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

    SendCharacterStatsEnterWorld();
    SendCharacterPosition();

    WorldPacket data(SMSG_SEND_CHAR_POSITION);
    data << character->GetPositionX();
    data << character->GetPositionY();
    SendPacket(data);

    SendUpdateObject();

    // Tmp test
    WorldPacket data2(SMSG_INTERACTIVE_ELEMENTS);
    data2 << quint16(1);
    data2 << quint64(20114);
    data2 << quint16(18);
    data2 << quint8(1);
    data2 << quint8(2);
    data2 << quint32(6);
    data2 << quint8(1);
    data2 << quint16(1);
    data2 << quint8(1);
    data2 << quint8(1);
    data2 << quint8(1);
    data2 << quint8(1);
    data2 << quint32(1);
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
        data << quint8(6); // Char part Id => ?
        data << character->GetGuid();
        data << quint8(0); // idType => ?
        data << GetAccountInfos().id;
        data.WriteString(character->GetName(), true);
        data << character->GetBreed();
        data << character->GetHealth();

        // *** Position, map
            data << character->GetPositionX();
            data << character->GetPositionY();
            data << character->GetPositionZ();
            data << character->GetInstanceId();
            data << character->GetDirection();
        // *****************

        // *** Skin
            data << character->GetGender();
            data << character->GetSkinColor();
            data << character->GetHairColor();
            data << character->GetPupilColor();
            data << character->GetSkinColorFactor();
            data << character->GetHairColorFactor();
            data << character->GetClothIndex();
            data << character->GetFaceIndex();
        // ********

        // *** Titles
            data << qint16(-1); // Titles
        // **********

        // *** Inventory
            data << quint16(0); // Inventory size
        // *************

        // *** Emote Id
            data << quint16(1); // Size
            data << quint32(20015); // EmoteId
        // ************

        // *** Landmark
            data << quint16(1); // Size
            data << quint8(30); // LandmarkId
        // ************

        data << quint16(0); // ZaapsCount
        data << quint16(0); // dragosCount
        data << quint16(0); // boatscount
        data << quint16(0); // cannonCount
        data << quint16(0); // phoenixCount
        data << qint32(-1); // selectedPhoenix

        // *** Spell Inventory
        data << quint16(0); // spellInventoryVersion
        data << quint32(0); // lockedSpellId
        data << quint16(0); // Spell size
        // *******************

        // *** Equipment Inventory
        data << quint16(0); // Count
        data << quint16(0); // questInvCount
        data << quint16(0); // tempInvCount
        // ***********************

        // *** Bags
            data << quint16(0); // Bags count
        // ********

        // *** BreedSpecific
            data << quint8(0); // hasOsaSpecific
        // *****************

        // *** SkillInventory
            data << quint16(0); // SkillInventory size
        // ******************

        // *** Craft
        data << quint16(0); // Craft count
        // *********


        // *** AptitudeInventory
        data << quint16(0); // Count
        // *********************

        // *** AptitudeInventory2
        data << quint16(0); // Count
        // *********************

        data << quint16(21); // Unk
        data << quint8(0); // hasInFightData
        data << quint8(0); // hasOutFightData

        // *** DimensionalBagLocalClient
        data << character->GetGuid();
        data.WriteString(character->GetName(), true);
        data << character->GetGuildId();
        data << quint8(0); // Rooms count

        data << quint32(408); // CustomViewModelId
        data << quint8(0); // HasWallet
        data << quint8(0); // dimensionalBagLocked

        data << quint16(0); // groupeEntriesSize
        data << quint16(0); // IndividualEntriesSize
        // *****************************

        // *** Challenges
        data << quint8(0); // hasCurrentScenario
        data << quint8(0); // HasCurrentChallengeInfo
        data << quint16(0); // pastScnerioSize
        // **************

        // *** XP
        data << character->GetXP();
        data << character->GetXPFreePoints();
        data << quint16(0); // xpBonusPoints size
        data << quint16(0); // m_characteristicBonusPoints size
        data << character->GetXPGauge();
        // ******

        // *** Titles
        data << quint16(0); // availableTitlesCount
        // **********

        // *** CitizenPoint
        data << quint16(0); // nationCitizenScoresSize
        data << quint16(0); // offendedNationsSize
        // **********

        // *** PassportInfo
        data << quint8(0); // isPassportActive
        // ****************

        // *** SocialStates
        data << quint8(0); // afkState
        data << quint8(0); // dndstate
        // ****************

        // *** Pet
        data << quint8(0); // HasPet
        // *******

        // *** AchievementsData
        data << quint16(0); // Size
        // ********************

        // *** LockToClient
        data << quint16(0); // Lock size ?
        // ****************

        // *** Unknown
        for (quint16 j = 0; j < 302; ++j)
            data << quint8(0);

        // *** AccountInformation
        data << quint32(0); // AdminRights
        data << quint32(1); // AccountFlags
        // **********************

        // *** DimensionalBagViewsInventory
        data << quint16(0); // Size
        // ********************************

        // *** Unk
        data << quint16(0); // Size
        data << quint8(0);
        data << quint8(0);
        data << quint8(0);
        data << quint8(0);
        data << quint8(0);
        // *******
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
        data << quint8(22); // Unk
        data << character->GetGuid();
        data << quint8(0); // idType
        data << GetAccountInfos().id;

        data << character->GetPositionX();
        data << character->GetPositionY();
        data << character->GetPositionZ();
        data << character->GetInstanceId();
        data << character->GetDirection();
    }
    data.EndBlock<quint16>();

    data.StartBlock<quint16>();
    {
        data << quint16(0); // Protectors size
        // TODO : bnY.java

        data << quint16(0); // Size of something else ?
        data << quint16(0);
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}

void WorldSession::HandleSwitchChar(WorldPacket& /*packet*/)
{
    // Save perso, delete pointer, etc...
    SendCharactersList();
}
