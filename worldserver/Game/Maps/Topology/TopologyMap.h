#ifndef TOPOLOGYMAP_H
#define TOPOLOGYMAP_H

#include <QtCore>

#include "Maps/SimpleBinaryReader.h"

class TopologyMap
{
public:
    TopologyMap(SimpleBinaryReader* reader)
    {
        _reader = reader;
    }

    ~TopologyMap() { delete _reader; }

    virtual void read()
    {
        m_x = _reader->readShort() * 18;
        m_y = _reader->readShort() * 18;
        m_z = _reader->readShort();
    }

    virtual qint8 isCellBlocked(int x, int y) = 0;

    bool isInMap(int x, int y)
    {
        return x >= m_x && x < m_x + 18 && y >= m_y && y < m_y + 18;
    }

protected:
    SimpleBinaryReader* _reader;
    qint8 _type;

    int m_x;
    int m_y;
    qint16 m_z;

};

#endif // TOPOLOGYMAP_H
