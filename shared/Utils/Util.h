#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

class Utils
{
public:
    static QByteArray FromHexString(QString packet);
    static QString HashPassword(QString account, QString password);
    static qint32 irand(qint32 min, qint32 max);
    static quint32 urand(quint32 min, quint32 max);
    static qint32 randList(QList<qint32> list);
};

#endif
