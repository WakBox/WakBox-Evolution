#include "ConfigMgr.h"
#include "Logs/Log.h"

template<> ConfigMgr*  Singleton<ConfigMgr>::m_instance = 0;

ConfigMgr::ConfigMgr()
{
    m_world = NULL;
}
ConfigMgr::~ConfigMgr()
{
    if (m_world)
        delete m_world;

    m_world = NULL;
}

bool ConfigMgr::LoadWorldConfig(QString fileName)
{
    Configuration* worldConfig = new Configuration();
    m_world = worldConfig->OpenFile(fileName);

    if (m_world)
        return true;

    return false;
}
