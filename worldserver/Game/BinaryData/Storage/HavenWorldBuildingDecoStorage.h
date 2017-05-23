#ifndef BINARYDATA_HAVENWORLDBUILDINGDECOSTORAGE_H
#define BINARYDATA_HAVENWORLDBUILDINGDECOSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBuildingDecoStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBuildingDecoStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBuildingDecoBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_catalogEntryId = this->_reader->ReadShort();
            entry.m_kamaCost = this->_reader->ReadInt();
            entry.m_ressourceCost = this->_reader->ReadInt();
            entry.m_editorGroupId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBuildingDecoStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBUILDINGDECOSTORAGE_H
