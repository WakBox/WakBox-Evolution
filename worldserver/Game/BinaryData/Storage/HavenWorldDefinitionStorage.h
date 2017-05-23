#ifndef BINARYDATA_HAVENWORLDDEFINITIONSTORAGE_H
#define BINARYDATA_HAVENWORLDDEFINITIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldDefinitionStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldDefinitionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldDefinitionBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_worldId = this->_reader->ReadShort();
            entry.m_workers = this->_reader->ReadByte();
            entry.m_exitWorldId = this->_reader->ReadShort();
            entry.m_exitCellX = this->_reader->ReadShort();
            entry.m_exitCellY = this->_reader->ReadShort();
            entry.m_exitCellZ = this->_reader->ReadShort();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldDefinitionStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDDEFINITIONSTORAGE_H
