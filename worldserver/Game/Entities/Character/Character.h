#ifndef CHARACTER_H
#define CHARACTER_H

#include "Databases/Database.h"
#include "Define.h"
#include "Server/WorldSession.h"
#include "Entities/Unit/Unit.h"

struct sCharacterCreateInfos
{
    sCharacterCreateInfos(QString name, quint16 breed, quint8 gender, quint8 skinColor, quint8 hairColor, quint8 pupilColor,
                          quint8 skinColorFactor, quint8 hairColorFactor, quint8 cloth, quint8 face) :
        name(name), breed(breed), gender(gender), skinColor(skinColor), hairColor(hairColor), pupilColor(pupilColor),
        skinColorFactor(skinColorFactor), hairColorFactor(hairColorFactor), cloth(cloth), face(face) {}

    QString name;
    quint16 breed;

    quint8 gender, skinColor, hairColor, pupilColor;
    quint8 skinColorFactor, hairColorFactor, cloth, face;
};

class Character : public Unit
{
public:
    Character(WorldSession* session);
    ~Character();

    WorldSession* GetSession() { return m_session; }

    bool Create(quint64 guid, sCharacterCreateInfos characterCreateInfos);
    bool LoadFromDB(quint64 guid);
    void SaveToDB(bool create = false);

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
    quint8 m_cloth;
    quint8 m_face;
};

#endif // CHARACTER_H
