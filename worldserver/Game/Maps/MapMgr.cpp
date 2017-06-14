#include "MapMgr.h"
#include "Logs/Log.h"

template<> MapMgr*  Singleton<MapMgr>::m_instance = 0;

MapMgr::MapMgr()
{

}

MapMgr::~MapMgr()
{

}

Map* MapMgr::CreateMap(qint16 id)
{
    Map* map = FindMap(id);

    if (!map)
    {
        map = new Map(id);
        m_maps[id] = map;
    }

    return map;
}
