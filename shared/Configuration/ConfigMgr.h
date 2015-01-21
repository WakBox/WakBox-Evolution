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

    Configuration* GetAuthConfig()
    {
        return m_auth;
    }

    Configuration* GetWorldConfig()
    {
        return m_world;
    }

    bool LoadAuthConfig(QString fileName);
    bool LoadWorldConfig(QString fileName);

    bool FileExists(QString name);

private:
    Configuration* m_auth;
    Configuration* m_world;
};

#define sConfigMgr ConfigMgr::Instance()
#define sAuthConfig sConfigMgr->GetAuthConfig()
#define sWorldConfig sConfigMgr->GetWorldConfig()

#endif
