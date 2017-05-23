#ifndef BINARYDATA_COMPANIONITEMSTORAGE_H
#define BINARYDATA_COMPANIONITEMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CompanionItemStorage : public BinaryDataStorage<T>
{
public:
    CompanionItemStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CompanionItemBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CompanionItemStorage";
    }
};

#endif // BINARYDATA_COMPANIONITEMSTORAGE_H
