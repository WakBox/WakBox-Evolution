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
