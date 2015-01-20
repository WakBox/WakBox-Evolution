#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class Utils
{
public:
    static QByteArray FromHexString(QString packet);
    static QString HashPassword(QString username, QString password);
    static QString GenerateToken(QString username);
};

#endif
