#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class Utils
{
public:
    static QByteArray FromHexString(QString packet);
    static QString HashPassword(QString username, QString password);
    static QString GenerateToken(QString username);

    static qint16 getIntFromTwoInt(qint16 a, qint16 b)
    {
        return a << 16 | (b & 0xFFFF);
    }
};

#endif
