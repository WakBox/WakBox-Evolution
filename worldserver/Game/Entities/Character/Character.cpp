#include "Character.h"
#include "Server/WorldSession.h"
#include "Utils/Util.h"

Character::Character(WorldSession* session) : Unit()
{
    m_session = session;
    m_typeId = TYPEID_CHARACTER;

    m_xp = 0;
    m_title = -1;

    m_gender = 0;
    m_skinColor = 0;
    m_hairColor = 0;
    m_pupilColor = 0;
    m_skinColorFactor = 0;
    m_hairColorFactor = 0;
    m_clothIndex = 0;
    m_faceIndex = 0;
}

Character::~Character()
{
}

bool Character::Create(quint64 guid, sCharacterCreateInfos characterCreateInfos)
{
    SetGuid(guid);

    SetName(characterCreateInfos.name);
    SetBreed(characterCreateInfos.breed);

    m_gender            = characterCreateInfos.gender;
    m_skinColor         = characterCreateInfos.skinColor;
    m_hairColor         = characterCreateInfos.hairColor;
    m_pupilColor        = characterCreateInfos.pupilColor;
    m_skinColorFactor   = characterCreateInfos.skinColorFactor;
    m_hairColorFactor   = characterCreateInfos.hairColorFactor;
    m_clothIndex        = characterCreateInfos.clothIndex;
    m_faceIndex         = characterCreateInfos.faceIndex;

    return true;
}

bool Character::LoadFromDB(quint64 guid)
{
    QSqlQuery result = sCharDatabase->Query(SELECT_CHARACTER_BY_GUID_AND_ACCOUNT, QVariantList() << guid << GetSession()->GetAccountInfos().id);

    if (!result.first())
    {
        qDebug() << "Character::LoadFromDB character with guid " << guid << " not found or wrong account";
        return false;
    }

    m_guid              = guid;

    SetName(result.value("name").toString());
    SetBreed(result.value("breed").toUInt());
    SetLevel(result.value("level").toUInt());

    m_xp                = result.value("xp").toULongLong();
    m_title             = result.value("title").toLongLong();

    m_gender            = result.value("gender").toUInt();
    m_skinColor         = result.value("skin_color").toUInt();
    m_hairColor         = result.value("hair_color").toUInt();
    m_pupilColor        = result.value("pupil_color").toUInt();
    m_skinColorFactor   = result.value("skin_color_factor").toUInt();
    m_hairColorFactor   = result.value("hair_color_factor").toUInt();
    m_clothIndex        = result.value("cloth").toUInt();
    m_faceIndex         = result.value("face").toUInt();

    SetPosition(result.value("position_x").toInt(), result.value("position_y").toInt(), result.value("position_z").toInt());

    SetDirection(result.value("direction").toInt());
    SetInstanceId(result.value("instance_id").toInt());

    GetSession()->SetCharacter(this);
    return true;
}

bool Character::SaveToDB(bool create)
{
    if (create)
    {
        QSqlQuery result = sCharDatabase->Query(INSERT_CHARACTER, QVariantList()
                                << GetGuid() << GetSession()->GetAccountInfos().id << GetName() << GetBreed() << m_gender << GetLevel() << m_xp
                                << m_skinColor << m_hairColor << m_pupilColor << m_skinColorFactor << m_hairColorFactor << m_clothIndex << m_faceIndex << m_title
                                << GetPositionX() << GetPositionY() << GetPositionZ() << GetDirection() << GetInstanceId());

        if (result.lastError().number() > QSqlError::NoError)
            return false;

        //Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetSession()->GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), GetSession()->GetCharsCount() + 1);
    }
    else
    {
        sCharDatabase->Query(UPDATE_CHARACTER, QVariantList()
                                << GetPositionX() << GetPositionY() << GetPositionZ() << GetDirection() << GetInstanceId() << GetGuid());
    }

    return true;
}

// Temporary - handling of this packet should be different!
void Character::SendActorDespawn()
{
    WorldPacket data(SMSG_ACTOR_DESPAWN);
    data << quint8(0); // bool m_applyApsOnDespawn
    data << quint8(0); // bool m_fightDespawn
    data << quint8(1); // actorsCount

    {
        data << quint8(0); // Actor type
        data << GetGuid();
    }

    // Send only for player in area
    sWorld->SendGlobalPacket(data, GetSession());
}
