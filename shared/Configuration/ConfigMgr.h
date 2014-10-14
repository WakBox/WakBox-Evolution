#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <QtCore>
#include "Configuration.h"
#include "Utils/Singleton.h"

class ConfigMgr : public Singleton<ConfigMgr>
{
public:
    ConfigMgr();
    ~ConfigMgr();

    Configuration* GetWorldConfig() { Q_ASSERT(m_world); return m_world; }
    bool LoadWorldConfig(QString fileName);

private:
    Configuration* m_world;
};

#define sConfigMgr ConfigMgr::Instance()
#define sWorldConfig sConfigMgr->GetWorldConfig()

#endif
