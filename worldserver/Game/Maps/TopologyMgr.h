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

typedef QHash<QString, TopologyMap*> TopologyMapHash;
typedef QHash<quint16, TopologyMapHash> TopologyMapsHash;

class TopologyMgr : public Singleton<TopologyMgr>
{
public:
    TopologyMgr();
    ~TopologyMgr();

    void LoadTopology();

private:
    TopologyMapsHash m_topologyMaps;
};

#define sTopologyMgr TopologyMgr::Instance()

#endif // TOPOLOGYMGR_H
