#include "Util.h"

QByteArray Utils::FromHexString(QString packet)
{
    QString stripped = packet.remove(QRegExp("[^a-zA-Z0-9]")); //Removes everything except a-z (and capital) and 0-9

    //Error, its not an even numbered string (so not in correct form)
    if (stripped.size() % 2 != 0)
        return NULL;

    QByteArray buffer(stripped.size() % 2, '\0');
    int strippedSize = stripped.size();
    bool good;

    for (int i = 0; i < strippedSize; i += 2)
    {
        QStringRef hex(&stripped, i, 2);
        quint8 c = (quint8)hex.toString().toUShort(&good, 16);

        if(!good)
            return NULL;

        buffer.push_back(c);
    }

    return buffer;
}

QString Utils::HashPassword(QString username, QString password)
{
    QString data = username + ":" + password;
    return QString(QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Sha1).toHex());
}

QString Utils::GenerateToken(QString username)
{
    QString data = username + "-" + QDateTime::currentDateTime().toMSecsSinceEpoch();
    return QString(QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Sha1).toHex());
}
