#include "Configuration.h"
#include "Logs/Log.h"

Configuration::Configuration()
{
    m_file = NULL;
    m_config.clear();
}
Configuration::~Configuration()
{
    if (m_file)
        m_file->close();

    m_file = NULL;
    m_config.clear();
}

Configuration* Configuration::OpenFile(QString fileName)
{
    m_file = new QFile(fileName);
    if(!m_file->open(QIODevice::ReadOnly))
    {
        QString error = m_file->errorString();
        cout << "Cannot open configuration file " << fileName.toLatin1().data() << " : " << error.toLatin1().data() << endl;

        delete m_file;
        return NULL;
    }

    QSettings settings(fileName, QSettings::IniFormat);
    const QStringList keys = settings.allKeys();


    QStringList::const_iterator itr;
    for (itr = keys.constBegin(); itr != keys.constEnd(); ++itr)
        m_config.insert((*itr), settings.value((*itr)).toString());

    cout << "Configuration file " << fileName.toLatin1().data() << " successfully loaded." << endl;
    m_file->close();
    return this;
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
