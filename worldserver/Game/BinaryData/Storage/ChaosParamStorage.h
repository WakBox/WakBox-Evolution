#ifndef BINARYDATA_CHAOSPARAMSTORAGE_H
#define BINARYDATA_CHAOSPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ChaosParamStorage : public BinaryDataStorage<T>
{
public:
    ChaosParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ChaosParamBinaryData entry;

            entry.m_chaosLevel = this->_reader->ReadByte();
            entry.m_chaosCollectorParamId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ChaosParamStorage";
    }
};

#endif // BINARYDATA_CHAOSPARAMSTORAGE_H
