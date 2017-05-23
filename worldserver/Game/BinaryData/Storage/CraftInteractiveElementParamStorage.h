#ifndef BINARYDATA_CRAFTINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_CRAFTINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CraftInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    CraftInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CraftInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_apsId = this->_reader->ReadInt();
            entry.m_visualMruId = this->_reader->ReadInt();
            entry.m_skillId = this->_reader->ReadInt();
            entry.m_allowedRecipes = this->_reader->ReadIntArray();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CraftInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_CRAFTINTERACTIVEELEMENTPARAMSTORAGE_H
