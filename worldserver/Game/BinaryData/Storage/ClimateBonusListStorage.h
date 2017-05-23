#ifndef BINARYDATA_CLIMATEBONUSLISTSTORAGE_H
#define BINARYDATA_CLIMATEBONUSLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ClimateBonusListStorage : public BinaryDataStorage<T>
{
public:
    ClimateBonusListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ClimateBonusListBinaryData entry;

            entry.m_buffListId = this->_reader->ReadInt();
            entry.m_entries = this->_reader->ReadIntArray();

            this->m_entries[entry.m_buffListId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ClimateBonusListStorage";
    }
};

#endif // BINARYDATA_CLIMATEBONUSLISTSTORAGE_H
