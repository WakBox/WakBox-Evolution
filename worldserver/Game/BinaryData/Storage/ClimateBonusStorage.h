#ifndef BINARYDATA_CLIMATEBONUSSTORAGE_H
#define BINARYDATA_CLIMATEBONUSSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ClimateBonusStorage : public BinaryDataStorage<T>
{
public:
    ClimateBonusStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ClimateBonusBinaryData entry;

            entry.m_buffId = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_criteria = this->_reader->ReadString();
            entry.m_duration = this->_reader->ReadInt();
            entry.m_price = this->_reader->ReadShort();
            entry.m_temperatureDifference = this->_reader->ReadFloat();
            entry.m_rainDifference = this->_reader->ReadFloat();
            entry.m_windDifference = this->_reader->ReadFloat();

            this->m_entries[entry.m_buffId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ClimateBonusStorage";
    }
};

#endif // BINARYDATA_CLIMATEBONUSSTORAGE_H
