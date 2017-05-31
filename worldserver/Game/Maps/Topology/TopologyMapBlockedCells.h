#ifndef TOPOLOGYMAPBLOCKEDCELLS_H
#define TOPOLOGYMAPBLOCKEDCELLS_H

#include <QtCore>

#include "TopologyMap.h"

class TopologyMapBlockedCells : public TopologyMap
{
public:
    TopologyMapBlockedCells(SimpleBinaryReader* reader) : TopologyMap(reader) { }

    virtual void read()
    {
        TopologyMap::read();

        m_blockedCells.reserve((324 + 7) >> 3);

        for (int i = 0; i < m_blockedCells.capacity(); ++i)
            m_blockedCells.push_back(_reader->readByte());
    }

    virtual qint8 isCellBlocked(int x, int y)
    {
        int index = (y - m_y) * 18 + x - m_x;
        int unitPosition = index >> 3;

        if (unitPosition >= m_blockedCells.size())
            return -1;

        int bitPosition = 7 - (index - (unitPosition << 3));

        return (m_blockedCells[unitPosition] & 1 << bitPosition) != 0;
    }

protected:
    QVector<qint8> m_blockedCells;
};

#endif // TOPOLOGYMAPBLOCKEDCELLS_H
