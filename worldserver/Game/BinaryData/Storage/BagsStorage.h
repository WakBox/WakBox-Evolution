#ifndef BINARYDATA_BAGSSTORAGE_H
#define BINARYDATA_BAGSSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BagsStorage : public BinaryDataStorage<T>
{
public:
    BagsStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BagsBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_capacity = this->_reader->ReadShort();
            entry.m_bagType = this->_reader->ReadInt();
            entry.m_validItemCategories = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BagsStorage";
    }
};

#endif // BINARYDATA_BAGSSTORAGE_H
