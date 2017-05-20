#include "BinaryData.h"

AchievementStorage<AchievementBinaryData> sAchievement;

template<class T>
inline void LoadStorage(BinaryDataStorage<T>& storage, QString filename)
{
    QFile file("bdata/" + filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        // todo error handling
        qDebug() << "BinaryStorage file : " << filename << " not found!";
        return;
    }

    QByteArray bdata = file.readAll();
    quint8 fileId = (quint8)QFileInfo(filename).fileName().split(".").at(0).toUInt();

    storage.InitWith(bdata, fileId);
    storage.Load();
}

void LoadBinaryStorage()
{
    LoadStorage(sAchievement, "1.bin");
}
