#ifndef TOPOLOGYMGR_H
#define TOPOLOGYMGR_H

#include "Utils/Singleton.h"
#include "quazip/JlCompress.h"
#include "Topology/TopologyMap.h"
#include "Topology/TopologyMapA.h"
#include "Topology/TopologyMapB.h"
#include "Topology/TopologyMapBi.h"
#include "Topology/TopologyMapC.h"
#include "Topology/TopologyMapCi.h"
#include "Topology/TopologyMapDi.h"

typedef QHash<quint16, TopologyMap*> TopologyMapHash;

class TopologyMgr : public Singleton<TopologyMgr>
{
public:
    TopologyMgr();
    ~TopologyMgr();

    // What's worldId?
    long GetHashCode(int worldId, long x, long y, int uniqueInstanceId = 0)
    {
        x += 32767L;
        y += 32767L;
        return x << 48 | y << 32 | (worldId & 0xFFFF) << 16 | (uniqueInstanceId & 0xFFFF);
    }

    void LoadTopology();

private:
    TopologyMapHash m_topologyMaps;
};

#endif // TOPOLOGYMGR_H
