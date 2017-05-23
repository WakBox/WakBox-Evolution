#ifndef BINARYDATA_NATIONRANKSTORAGE_H
#define BINARYDATA_NATIONRANKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class NationRankStorage : public BinaryDataStorage<T>
{
public:
    NationRankStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            NationRankBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_citizenPointLossFactor = this->_reader->ReadFloat();
            entry.m_criteria = this->_reader->ReadString();
            entry.m_citizenScoreLine = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for NationRankStorage";
    }
};

#endif // BINARYDATA_NATIONRANKSTORAGE_H
