#ifndef BINARYDATA_APTITUDEBONUSSTORAGE_H
#define BINARYDATA_APTITUDEBONUSSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AptitudeBonusStorage : public BinaryDataStorage<T>
{
public:
    AptitudeBonusStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AptitudeBonusBinaryData entry;

            entry.m_bonusId = this->_reader->ReadInt();
            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_max = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_effectIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_bonusId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AptitudeBonusStorage";
    }
};

#endif // BINARYDATA_APTITUDEBONUSSTORAGE_H
