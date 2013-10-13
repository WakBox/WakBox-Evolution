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

    Configuration* GetAuthConfig() { Q_ASSERT(m_auth); return m_auth; }
    Configuration* GetWorldConfig() { Q_ASSERT(m_world); return m_world; }

    static Configuration* Auth() { return ConfigMgr::Instance()->GetAuthConfig(); }
    static Configuration* World() { return ConfigMgr::Instance()->GetWorldConfig(); }

    bool LoadAuthConfig(QString fileName);
    bool LoadWorldConfig(QString fileName);

private:
    Configuration* m_auth;
    Configuration* m_world;
};

#endif
