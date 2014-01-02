#include "Character.h"
#include "Utils/Util.h"

Character::Character(WorldSession* session) : Unit()
{
    m_session = session;
    m_typeId = TYPEID_CHARACTER;

    m_name = QString();
    m_breed = 0;

    m_level = 1;
    m_xp = 0;
    m_title = -1;

    m_gender = 0;
    m_skinColor = 0;
    m_hairColor = 0;
    m_pupilColor = 0;
    m_skinColorFactor = 0;
    m_hairColorFactor = 0;
    m_cloth = 0;
    m_face = 0;
}

Character::~Character()
{
}

bool Character::Create(quint64 guid, sCharacterCreateInfos characterCreateInfos)
{
    SetGuid(guid);

    m_name              = characterCreateInfos.name;
    m_breed             = characterCreateInfos.breed;

    m_gender            = characterCreateInfos.gender;
    m_skinColor         = characterCreateInfos.skinColor;
    m_hairColor         = characterCreateInfos.hairColor;
    m_pupilColor        = characterCreateInfos.pupilColor;
    m_skinColorFactor   = characterCreateInfos.skinColorFactor;
    m_hairColorFactor   = characterCreateInfos.hairColorFactor;
    m_cloth             = characterCreateInfos.cloth;
    m_face              = characterCreateInfos.face;

    return true;
}

bool Character::LoadFromDB(quint64 guid)
{
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_BY_GUID_AND_ACCOUNT, QVariantList() << guid << GetSession()->GetAccountInfos().id);

    if (!result.first())
    {
        qDebug() << "Character::LoadFromDB character with guid " << guid << " not found or wrong account";
        return false;
    }

    QSqlRecord fields = result.record();

    m_guid              = guid;

    m_name              = result.value(fields.indexOf("name")).toString();
    m_breed             = (quint16)result.value(fields.indexOf("breed")).toUInt();

    m_level             = (quint16)result.value(fields.indexOf("level")).toUInt();
    m_xp                = (quint64)result.value(fields.indexOf("xp")).toULongLong();
    m_title             = (qint64)result.value(fields.indexOf("title")).toLongLong();

    m_gender            = (quint8)result.value(fields.indexOf("gender")).toUInt();
    m_skinColor         = (quint8)result.value(fields.indexOf("skin_color")).toUInt();
    m_hairColor         = (quint8)result.value(fields.indexOf("hair_color")).toUInt();
    m_pupilColor        = (quint8)result.value(fields.indexOf("pupil_color")).toUInt();
    m_skinColorFactor   = (quint8)result.value(fields.indexOf("skin_color_factor")).toUInt();
    m_hairColorFactor   = (quint8)result.value(fields.indexOf("hair_color_factor")).toUInt();
    m_cloth             = (quint8)result.value(fields.indexOf("cloth")).toUInt();
    m_face              = (quint8)result.value(fields.indexOf("face")).toUInt();

    GetSession()->SetCharacter(this);
    return true;
}

void Character::SaveToDB(bool create)
{
    if (create)
    {
        Database::Char()->Query(INSERT_CHARACTER, QVariantList()
                                << GetGuid() << GetSession()->GetAccountInfos().id << m_name << m_breed << m_gender << m_level << m_xp
                                << m_skinColor << m_hairColor << m_pupilColor << m_skinColorFactor << m_hairColorFactor << m_cloth << m_face << m_title);

        //Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetSession()->GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), GetSession()->GetCharsCount() + 1);
    }
    else
    {
        // Todo update player
    }
}
