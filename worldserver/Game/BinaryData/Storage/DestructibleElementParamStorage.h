#ifndef BINARYDATA_DESTRUCTIBLEELEMENTPARAMSTORAGE_H
#define BINARYDATA_DESTRUCTIBLEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DestructibleElementParamStorage : public BinaryDataStorage<T>
{
public:
    DestructibleElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DestructibleElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_pdv = this->_reader->ReadInt();
            entry.m_regenDelay = this->_reader->ReadInt();
            entry.m_resWater = this->_reader->ReadInt();
            entry.m_resFire = this->_reader->ReadInt();
            entry.m_resEarth = this->_reader->ReadInt();
            entry.m_resWind = this->_reader->ReadInt();
            entry.m_effectIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DestructibleElementParamStorage";
    }
};

#endif // BINARYDATA_DESTRUCTIBLEELEMENTPARAMSTORAGE_H
