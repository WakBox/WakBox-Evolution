#ifndef BINARYDATA_ALMANACHDATESTORAGE_H
#define BINARYDATA_ALMANACHDATESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AlmanachDateStorage : public BinaryDataStorage<T>
{
public:
    AlmanachDateStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AlmanachDateBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_date = this->_reader->ReadLong();
            entry.m_almanachEntryId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AlmanachDateStorage";
    }
};

#endif // BINARYDATA_ALMANACHDATESTORAGE_H
