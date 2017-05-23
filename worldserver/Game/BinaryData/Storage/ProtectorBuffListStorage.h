#ifndef BINARYDATA_PROTECTORBUFFLISTSTORAGE_H
#define BINARYDATA_PROTECTORBUFFLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ProtectorBuffListStorage : public BinaryDataStorage<T>
{
public:
    ProtectorBuffListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ProtectorBuffListBinaryData entry;

            entry.m_buffListId = this->_reader->ReadInt();
            entry.m_buffLists = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ProtectorBuffListStorage";
    }
};

#endif // BINARYDATA_PROTECTORBUFFLISTSTORAGE_H
