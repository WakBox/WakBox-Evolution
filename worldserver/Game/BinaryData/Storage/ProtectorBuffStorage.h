#ifndef BINARYDATA_PROTECTORBUFFSTORAGE_H
#define BINARYDATA_PROTECTORBUFFSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ProtectorBuffStorage : public BinaryDataStorage<T>
{
public:
    ProtectorBuffStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ProtectorBuffBinaryData entry;

            entry.m_buffId = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_criteria = this->_reader->ReadString();
            entry.m_origin = this->_reader->ReadByte();
            entry.m_effects = this->_reader->ReadIntArray();

            this->m_entries[entry.m_buffId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ProtectorBuffStorage";
    }
};

#endif // BINARYDATA_PROTECTORBUFFSTORAGE_H
