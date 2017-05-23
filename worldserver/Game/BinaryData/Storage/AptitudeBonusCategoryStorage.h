#ifndef BINARYDATA_APTITUDEBONUSCATEGORYSTORAGE_H
#define BINARYDATA_APTITUDEBONUSCATEGORYSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AptitudeBonusCategoryStorage : public BinaryDataStorage<T>
{
public:
    AptitudeBonusCategoryStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AptitudeBonusCategoryBinaryData entry;

            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_levels = this->_reader->ReadIntArray();
            entry.m_bonusIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_categoryId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AptitudeBonusCategoryStorage";
    }
};

#endif // BINARYDATA_APTITUDEBONUSCATEGORYSTORAGE_H
