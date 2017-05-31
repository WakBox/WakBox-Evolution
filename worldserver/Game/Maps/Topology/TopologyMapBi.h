#ifndef TOPOLOGYMAPBI_H
#define TOPOLOGYMAPBI_H

#include <QtCore>

#include "TopologyMapBlockedCells.h"

class TopologyMapBi : public TopologyMapBlockedCells
{
public:
    TopologyMapBi(SimpleBinaryReader* reader) : TopologyMapBlockedCells(reader) { _type = 2; }

    virtual void read()
    {
        TopologyMapBlockedCells::read();

        int indexSize = _reader->readByte();

        for (int i = 0; i < indexSize; ++i)
        {
            m_cost.push_back(_reader->readByte());
            m_murfin.push_back(_reader->readByte());
            m_property.push_back(_reader->readByte());
        }

        int cellSize = _reader->readByte() & 0xFF;
        for (int i = 0; i < cellSize; ++i)
            m_cells.push_back(_reader->readInt());
    }

private:
    QVector<qint8> m_cost;
    QVector<qint8> m_murfin;
    QVector<qint8> m_property;
    QVector<int> m_cells;
};

#endif // TOPOLOGYMAPBI_H
