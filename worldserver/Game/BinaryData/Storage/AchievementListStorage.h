#ifndef BINARYDATA_ACHIEVEMENTLISTSTORAGE_H
#define BINARYDATA_ACHIEVEMENTLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AchievementListStorage : public BinaryDataStorage<T>
{
public:
    AchievementListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AchievementListBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 elementCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < elementCount; ++i)
            {
                AchievementListData achievementListData;

                achievementListData.m_achievementId = this->_reader->ReadInt();
                achievementListData.m_order = this->_reader->ReadInt();

                entry.m_elements.push_back(achievementListData);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AchievementListStorage";
    }
};

#endif // BINARYDATA_ACHIEVEMENTLISTSTORAGE_H
