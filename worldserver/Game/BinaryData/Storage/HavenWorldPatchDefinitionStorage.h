#ifndef BINARYDATA_HAVENWORLDPATCHDEFINITIONSTORAGE_H
#define BINARYDATA_HAVENWORLDPATCHDEFINITIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldPatchDefinitionStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldPatchDefinitionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldPatchDefinitionBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_patchId = this->_reader->ReadInt();
            entry.m_kamaCost = this->_reader->ReadInt();
            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_soundId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldPatchDefinitionStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDPATCHDEFINITIONSTORAGE_H
