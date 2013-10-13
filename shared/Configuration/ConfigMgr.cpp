#include "ConfigMgr.h"
#include "Logs/Log.h"

template<> ConfigMgr*  Singleton<ConfigMgr>::m_instance = 0;

ConfigMgr::ConfigMgr()
{
    m_auth = NULL;
    m_world = NULL;
}
ConfigMgr::~ConfigMgr()
{
    if (m_auth)
        delete m_auth;

    if (m_world)
        delete m_world;

    m_auth = NULL;
    m_world = NULL;
}

bool ConfigMgr::LoadAuthConfig(QString fileName)
{
    Configuration* authConfig = new Configuration();
    m_auth = authConfig->OpenFile(fileName);

    if (m_auth)
        return true;

    return false;
}

bool ConfigMgr::LoadWorldConfig(QString fileName)
{
    Configuration* worldConfig = new Configuration();
    m_world = worldConfig->OpenFile(fileName);

    if (m_world)
        return true;

    return false;
}
