#include "Configuration.h"
#include "Logs/Log.h"

Configuration::Configuration(QString filename)
{
    m_filename = filename;
    m_config.clear();
}
Configuration::~Configuration()
{
    m_config.clear();
}

bool Configuration::Load()
{
    m_config.clear();

    QSettings settings(m_filename, QSettings::IniFormat);
    const QStringList keys = settings.allKeys();

    QStringList::const_iterator itr;
    for (itr = keys.constBegin(); itr != keys.constEnd(); ++itr)
        m_config.insert((*itr), settings.value((*itr)).toString());

    cout << "Configuration file " << m_filename.toLatin1().data() << " successfully loaded." << endl;
    return true;
}

QString Configuration::GetValue(QString name)
{
    ConfigMap::const_iterator i = m_config.find(name);
    if(i != m_config.end())
        return i.value();

    Log::Write(LOG_TYPE_NORMAL, "Trying to get config value \"%s\" but the value don't exist.", name.toLatin1().data());
    return QString();
}

QString Configuration::GetString(QString name)
{
    return GetValue(name);
}

bool Configuration::GetBool(QString name)
{
    QString val = GetValue(name);
    return (val.toLower() == "true" || val.toLower() == "yes" || val == "1");
}

int Configuration::GetInt(QString name)
{
    return GetValue(name).toInt();
}

ushort Configuration::GetUShort(QString name)
{
    return GetValue(name).toUShort();
}

uint Configuration::GetUInt(QString name)
{
    return GetValue(name).toUInt();
}
