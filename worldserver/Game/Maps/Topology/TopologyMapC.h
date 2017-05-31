#ifndef TOPOLOGYMAPC_H
#define TOPOLOGYMAPC_H

#include <QtCore>

#include "TopologyMapBlockedCells.h"

class TopologyMapC : public TopologyMapBlockedCells
{
public:
    TopologyMapC(SimpleBinaryReader* reader) : TopologyMapBlockedCells(reader) { _type = 3; }

    virtual void read()
    {
        TopologyMapBlockedCells::read();

        for (int i = 0; i < 324; ++i)
        {
            m_cost.push_back(_reader->readByte());
            m_murfin.push_back(_reader->readByte());
            m_property.push_back(_reader->readByte());
            m_zs.push_back(_reader->readShort());
            m_heights.push_back(_reader->readByte());
            m_movLos.push_back(_reader->readByte());
        }
    }

private:
    QVector<qint8> m_cost;
    QVector<qint8> m_murfin;
    QVector<qint8> m_property;
    QVector<short> m_zs;
    QVector<qint8> m_heights;
    QVector<qint8> m_movLos;
};

#endif // TOPOLOGYMAPC_H
