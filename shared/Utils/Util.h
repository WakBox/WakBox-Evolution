#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class Utils
{
public:
    static QByteArray FromHexString(QString packet);
    static QString HashPassword(QString username, QString password);
    static QString GenerateToken(QString username);

    static qint32 getIntFromTwoInt(qint32 a, qint32 b)
    {
        return a << 16 | (b & 0xFFFF);
    }

    static qint16 getFirstShortFromInt(qint32 value)
    {
        return (qint16)(value >> 16 & 0xFFFF);
    }

    static qint16 getSecondShortFromInt(qint32 value)
    {
        return (qint16)(value & 0xFFFF);
    }
};

#endif
