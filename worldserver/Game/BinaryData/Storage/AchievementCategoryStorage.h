#ifndef BINARYDATA_ACHIEVEMENTCATEGORYSTORAGE_H
#define BINARYDATA_ACHIEVEMENTCATEGORYSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AchievementCategoryStorage : public BinaryDataStorage<T>
{
public:
    AchievementCategoryStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AchievementCategoryBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_parentId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AchievementCategoryStorage";
    }
};

#endif // BINARYDATA_ACHIEVEMENTCATEGORYSTORAGE_H
