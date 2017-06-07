#ifndef CHARACTER_H
#define CHARACTER_H

#include "Databases/Database.h"
#include "Define.h"
#include "Server/WorldSession.h"
#include "Entities/Unit/Unit.h"

struct sCharacterCreateInfos
{
    sCharacterCreateInfos(QString name, quint16 breed, quint8 gender, quint8 skinColor, quint8 hairColor, quint8 pupilColor,
                          quint8 skinColorFactor, quint8 hairColorFactor, quint8 clothIndex, quint8 faceIndex) :
        name(name), breed(breed), gender(gender), skinColor(skinColor), hairColor(hairColor), pupilColor(pupilColor),
        skinColorFactor(skinColorFactor), hairColorFactor(hairColorFactor), clothIndex(clothIndex), faceIndex(faceIndex) {}

    QString name;
    quint16 breed;

    quint8 gender, skinColor, hairColor, pupilColor;
    quint8 skinColorFactor, hairColorFactor, clothIndex, faceIndex;
};

class Character : public Unit
{
public:
    Character(WorldSession* session);
    ~Character();

    WorldSession* GetSession() { return m_session; }

    QString GetName() { return m_name; }
    quint16 GetBreed() { return m_breed; }
    quint8 GetGender() { return m_gender; }

    quint8 GetSkinColor() { return m_skinColor; }
    quint8 GetSkinColorFactor() { return m_skinColorFactor; }

    quint8 GetHairColor() { return m_hairColor; }
    quint8 GetHairColorFactor() { return m_hairColorFactor; }

    quint8 GetPupilColor() { return m_pupilColor; }
    quint8 GetClothIndex() { return m_clothIndex; }
    quint8 GetFaceIndex() { return m_faceIndex; }

    quint32 GetHealth() { return 55; }
    quint64 GetXP() { return 0; }
    quint16 GetXPFreePoints() { return 0; }
    quint32 GetXPGauge() { return 0; }

    void SetPosition(qint32 positionX, qint32 positionY, qint16 positionZ)
    {
        m_positionX = positionX;
        m_positionY = positionY;
        m_positionZ = positionZ;
    }

    qint32 GetPositionX() { return m_positionX; }
    qint32 GetPositionY() { return m_positionY; }
    qint16 GetPositionZ() { return m_positionZ; }

    void SetDirection(quint8 direction) { m_direction = direction; }
    quint8 GetDirection() { return m_direction; }

    void SetInstanceId(quint16 instanceId) { m_instanceId = instanceId; }
    quint16 GetInstanceId() { return m_instanceId; }

    quint64 GetGuildId() { return 0; }

    bool Create(quint64 guid, sCharacterCreateInfos characterCreateInfos);
    bool LoadFromDB(quint64 guid);
    bool SaveToDB(bool create = false);

    void SendActorDespawn();

    // Character Serialization

    // ID
    void SerializeGuid(WorldPacket& data);

    // IDENTITY
    void SerializeIdentity(WorldPacket& data);

    // NAME
    void SerializeName(WorldPacket& data);

    // BREED
    void SerializeBreed(WorldPacket& data);

    // GUILD_BLAZON
    void SerializeGuildBlazon(WorldPacket& data);

    // GUILD_ID
    void SerializeGuildId(WorldPacket& data);

    // HP
    void SerializeHP(WorldPacket& data);

    // POSITION
    void SerializePosition(WorldPacket& data);

    // APPEARANCE
    void SerializeAppearance(WorldPacket& data);

    // SHORTCUT_INVENTORIES
    void SerializeShortcutInventories(WorldPacket& data);

    // EMOTE_INVENTORY
    void SerializeEmoteInventory(WorldPacket& data);

    // LANDMARK_INVENTORY
    void SerializeLandmarkInventory(WorldPacket& data);

    // DISCOVERED_ITEMS
    void SerializeDiscoveredItems(WorldPacket& data);

    // SPELL_INVENTORY
    void SerializeSpellInventory(WorldPacket& data);

    // INVENTORIES
    void SerializeInventories(WorldPacket& data);

    // EQUIPMENT_INVENTORY
    void SerializeEquipmentInventory(WorldPacket& data);

    // BAGS
    void SerializeBags(WorldPacket& data);

    // PROTO_TEMPORARY_INVENTORY
    void SerializeProtoTemporaryInventory(WorldPacket& data);

    // BREED_SPECIFIC
    void SerializeBreedSpecific(WorldPacket& data);

    // SKILL_INVENTORY
    void SerializeSkillInventory(WorldPacket& data);

    // CRAFT
    void SerializeCraft(WorldPacket& data);

    // APTITUDE_INVENTORY
    void SerializeAptitudeInventory(WorldPacket& data);

    // RUNNING_EFFECTS
    void SerializeRunningEffects(WorldPacket& data);

    // DIMENSIONAL_BAG_FOR_LOCAL_CLIENT
    void SerializeDimensionalBagForLocalClient(WorldPacket& data);

    // CHALLENGES
    void SerializeChallenges(WorldPacket& data);

    // XP
    void SerializeXP(WorldPacket& data);

    // XP_CHARACTERISTICS
    void SerializeXPCharacteristics(WorldPacket& data);

    // TITLES
    void SerializeTitles(WorldPacket& data);

    // CITIZEN_POINT
    void SerializeCitizenPoint(WorldPacket& data);

    // PASSEPORT_INFO
    void SerializePasseportInfo(WorldPacket& data);

    // SOCIAL_STATES
    void SerializeSocialStates(WorldPacket& data);

    // PET
    void SerializePet(WorldPacket& data);

    // ACHIEVEMENTS
    void SerializeAchievements(WorldPacket& data);

    // ACCOUNT_INFORMATION
    void SerializeAccountInformation(WorldPacket& data);

    // LOCK_TO_CLIENT
    void SerializeLockToClient(WorldPacket& data);

    // DIMENSIONAL_BAG_VIEWS_INVENTORY
    void SerializeDimensionalBagViewsInventory(WorldPacket& data);

    // PERSONAL_EFFECTS
    void SerializePersonalEffects(WorldPacket& data);

    // ANTI_ADDICTION
    void SerializeAntiAddiction(WorldPacket& data);

    // WORLD_PROPERTIES
    void SerializeWorldProperties(WorldPacket& data);

    // VISIBILITY
    void SerializeVisibility(WorldPacket& data);

    // OCCUPATION
    void SerializeOccupation(WorldPacket& data);

    // SPELL_DECK
    void SerializeSpellDeck(WorldPacket& data);

    // APTITUDE_BONUS_INVENTORY
    void SerializeAptitudeBonusInventory(WorldPacket& data);

    // NATION_ID
    void SerializeNationId(WorldPacket& data);

    // NATION_SYNCHRO
    void SerializeNationSynchro(WorldPacket& data);

    // GUILD_LOCAL_INFO
    void SerializeGuildLocalInfo(WorldPacket& data);

    // NATION_PVP_MONEY
    void SerializeNationPvpMoney(WorldPacket& data);

    // PUBLIC_CHARACTERISTICS
    void SerializePublicCharacteristics(WorldPacket& data);

    // FIGHT_PROPERTIES
    void SerializeFightProperties(WorldPacket& data);

    // FIGHT
    void SerializeFight(WorldPacket& data);

    // EQUIPMENT_APPEARANCE
    void SerializeEquipmentAppearance(WorldPacket& data);

    // CURRENT_MOVEMENT_PATH
    void SerializeCurrentMovementPath(WorldPacket& data);

    // GROUP
    void SerializeGroup(WorldPacket& data);

    // GUILD_REMOTE_INFO
    void SerializeGuildRemoteInfo(WorldPacket& data);

    // ACCOUNT_INFORMATION_REMOTE
    void SerializeAccountInformationRemote(WorldPacket& data);

    // COSMETICS
    void SerializeCosmetics(WorldPacket& data);

    // DOWNSCALE_INFO
    void SerializeDownscaleInfo(WorldPacket& data);

private:
    WorldSession* m_session;

    QString m_name;
    quint16 m_breed;

    quint16 m_level;
    quint64 m_xp;
    qint64 m_title;

    quint8 m_gender;
    quint8 m_skinColor;
    quint8 m_hairColor;
    quint8 m_pupilColor;
    quint8 m_skinColorFactor;
    quint8 m_hairColorFactor;
    quint8 m_clothIndex;
    quint8 m_faceIndex;

    qint32 m_positionX;
    qint32 m_positionY;
    qint16 m_positionZ;
    quint8 m_direction;
    quint16 m_instanceId;
};

#endif // CHARACTER_H
