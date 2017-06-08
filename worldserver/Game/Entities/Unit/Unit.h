#ifndef UNIT_H
#define UNIT_H

#include "Entities/Object/Object.h"

class Unit : public Object
{
public:
    Unit();
    ~Unit();

    void SetName(QString name) { m_name = name; }
    QString GetName() { return m_name; }

    void SetBreed(quint16 breed) { m_breed = breed; }
    quint16 GetBreed() { return m_breed; }

    void SetLevel(quint16 level) { m_level = level; }
    quint16 GetLevel() { return m_level; }

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

private:
    QString m_name;
    quint16 m_breed;
    quint16 m_level;

    qint32 m_positionX;
    qint32 m_positionY;
    qint16 m_positionZ;
    quint8 m_direction;
    quint16 m_instanceId;
};

#endif // UNIT_H
