#ifndef MAPMGR_H
#define MAPMGR_H

#include "Utils/Singleton.h"
#include "Map.h"

struct Rect
{
    qint16 mapMinX;
    qint16 mapMinY;
    qint16 mapMaxX;
    qint16 mapMaxY;
};

typedef QHash<qint32/*id*/, Map*> MapHash;

class MapMgr : public Singleton<MapMgr>
{
public:
    MapMgr();
    ~MapMgr();

    static qint32 getMapCoordFromCell(qint32 cell)
    {
        float mapCoord = cell / 18.0f;
        qint32 v = (qint32)mapCoord;

        if (mapCoord >= 0.0f)
            return v;

        return (v == mapCoord) ? v : (v - 1);
    }

    static Rect getPartitionsFromCells(qint16 minX, qint16 minY, qint16 width, qint16 height)
    {
        Rect rect;
        rect.mapMinX = getMapCoordFromCell(minX);
        rect.mapMinY = getMapCoordFromCell(minY);
        rect.mapMaxX = getMapCoordFromCell(minX + width) + 1;
        rect.mapMaxY = getMapCoordFromCell(minY + height) + 1;

        return rect;
    }

    Map* CreateMap(qint32 id);
    Map* FindMap(qint32 id) const
    {
        MapHash::const_iterator it = m_maps.find(id);
        return (it != m_maps.end() ? it.value() : nullptr);
    }

private:
    MapHash m_maps;
};

#define sMapMgr MapMgr::Instance()

#endif // MAPMGR_H
