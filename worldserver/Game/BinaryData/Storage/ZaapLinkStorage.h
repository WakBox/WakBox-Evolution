#ifndef BINARYDATA_ZAAPLINKSTORAGE_H
#define BINARYDATA_ZAAPLINKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ZaapLinkStorage : public BinaryDataStorage<T>
{
public:
    ZaapLinkStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ZaapLinkBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_start = this->_reader->ReadInt();
            entry.m_end = this->_reader->ReadInt();
            entry.m_cost = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ZaapLinkStorage";
    }
};

#endif // BINARYDATA_ZAAPLINKSTORAGE_H
