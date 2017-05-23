#ifndef BINARYDATA_MONSTERTYPESTORAGE_H
#define BINARYDATA_MONSTERTYPESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MonsterTypeStorage : public BinaryDataStorage<T>
{
public:
    MonsterTypeStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MonsterTypeBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_parentId = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MonsterTypeStorage";
    }
};

#endif // BINARYDATA_MONSTERTYPESTORAGE_H
