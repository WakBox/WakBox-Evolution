#ifndef TOPOLOGYMAPA_H
#define TOPOLOGYMAPA_H

#include <QtCore>

#include "TopologyMap.h"

class TopologyMapA : public TopologyMap
{
public:
    TopologyMapA(SimpleBinaryReader* reader) : TopologyMap(reader) { _type = 0; }

    virtual void read()
    {
        TopologyMap::read();

        m_cost = _reader->readByte();
        m_murfin = _reader->readByte();
        m_property = _reader->readByte();
    }

    virtual qint8 isCellBlocked(int /*x*/, int /*y*/)
    {
        return m_cost == -1;
    }

private:
    qint8 m_cost;
    qint8 m_murfin;
    qint8 m_property;
};

#endif // TOPOLOGYMAPA_H
