#ifndef BINARYDATA_HAVENWORLDBUILDINGEVOLUTIONSTORAGE_H
#define BINARYDATA_HAVENWORLDBUILDINGEVOLUTIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBuildingEvolutionStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBuildingEvolutionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBuildingEvolutionBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_catalogEntryId = this->_reader->ReadShort();
            entry.m_fromId = this->_reader->ReadInt();
            entry.m_toId = this->_reader->ReadInt();
            entry.m_delay = this->_reader->ReadLong();
            entry.m_order = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBuildingEvolutionStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBUILDINGEVOLUTIONSTORAGE_H
