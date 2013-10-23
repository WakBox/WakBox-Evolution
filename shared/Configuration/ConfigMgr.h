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

    static Configuration* World() { return ConfigMgr::Instance()->GetWorldConfig(); }

    bool LoadWorldConfig(QString fileName);

private:
    Configuration* m_world;
};

#endif
