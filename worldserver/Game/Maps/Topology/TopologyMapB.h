#ifndef TOPOLOGYMAPB_H
#define TOPOLOGYMAPB_H

#include <QtCore>

#include "TopologyMapBlockedCells.h"

class TopologyMapB : public TopologyMapBlockedCells
{
public:
    TopologyMapB(SimpleBinaryReader* reader) : TopologyMapBlockedCells(reader) { _type = 1; }

    virtual void read()
    {
        TopologyMapBlockedCells::read();

        for (int i = 0; i < 324; ++i)
        {
            m_cost.push_back(_reader->readByte());
            m_murfin.push_back(_reader->readByte());
            m_property.push_back(_reader->readByte());
        }
    }

private:
    QVector<qint8> m_cost;
    QVector<qint8> m_murfin;
    QVector<qint8> m_property;
};

#endif // TOPOLOGYMAPB_H
