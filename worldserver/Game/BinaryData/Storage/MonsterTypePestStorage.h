#ifndef BINARYDATA_MONSTERTYPEPESTSTORAGE_H
#define BINARYDATA_MONSTERTYPEPESTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MonsterTypePestStorage : public BinaryDataStorage<T>
{
public:
    MonsterTypePestStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MonsterTypePestBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_familyId = this->_reader->ReadInt();
            entry.m_pestMonsterId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MonsterTypePestStorage";
    }
};

#endif // BINARYDATA_MONSTERTYPEPESTSTORAGE_H
