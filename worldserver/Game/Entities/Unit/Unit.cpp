#include "Unit.h"

Unit::Unit()
{
    m_typeId = TYPEID_UNIT;

    m_name = QString();
    m_breed = 0;
    m_level = 1;

    m_positionX = 0;
    m_positionY = 0;
    m_positionZ = 0;
    m_direction = 0;
    m_instanceId = 0;
}

Unit::~Unit()
{

}
