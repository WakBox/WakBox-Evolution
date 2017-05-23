#ifndef BINARYDATA_CITIZENRANKSTORAGE_H
#define BINARYDATA_CITIZENRANKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CitizenRankStorage : public BinaryDataStorage<T>
{
public:
    CitizenRankStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CitizenRankBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_cap = this->_reader->ReadInt();
            entry.m_pdcLossFactor = this->_reader->ReadInt();
            entry.m_translationKey = this->_reader->ReadString();
            entry.m_color = this->_reader->ReadString();
            entry.m_rules = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CitizenRankStorage";
    }
};

#endif // BINARYDATA_CITIZENRANKSTORAGE_H
