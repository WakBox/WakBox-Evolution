#ifndef BINARYDATA_DUNGEONSTORAGE_H
#define BINARYDATA_DUNGEONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DungeonStorage : public BinaryDataStorage<T>
{
public:
    DungeonStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DungeonBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_minLevel = this->_reader->ReadShort();
            entry.m_instanceId = this->_reader->ReadShort();
            entry.m_tps = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DungeonStorage";
    }
};

#endif // BINARYDATA_DUNGEONSTORAGE_H
