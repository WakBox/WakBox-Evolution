#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtCore>

typedef QMap<QString, QString> ConfigMap;

class Configuration
{
public:
    Configuration(QString filename);
    ~Configuration();

    QString GetString(QString name);
    bool GetBool(QString name);
    int GetInt(QString name);
    ushort GetUShort(QString name);
    uint GetUInt(QString name);

    bool Load();
    bool Reload() { return Load(); }

private:
    QString GetValue(QString name);

    QString m_filename;
    ConfigMap m_config;
};

#endif
