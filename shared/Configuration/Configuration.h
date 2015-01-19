#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtCore>

typedef QMap<QString, QString> ConfigMap;

class Configuration
{
public:
    Configuration();
    ~Configuration();

    QString GetString(QString name);
    bool GetBool(QString name);
    int GetInt(QString name);
    ushort GetUShort(QString name);
    uint GetUInt(QString name);

    Configuration* OpenFile(QString fileName);

private:
    QString GetValue(QString name);

    QFile* m_file;
    ConfigMap m_config;
};

#endif
