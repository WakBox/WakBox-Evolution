#ifndef BINARYDATA_MONSTERTYPEDUNGEONSTORAGE_H
#define BINARYDATA_MONSTERTYPEDUNGEONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MonsterTypeDungeonStorage : public BinaryDataStorage<T>
{
public:
    MonsterTypeDungeonStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MonsterTypeDungeonBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_familyId = this->_reader->ReadInt();
            entry.m_dungeonId = this->_reader->ReadInt();
            entry.m_level = this->_reader->ReadShort();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MonsterTypeDungeonStorage";
    }
};

#endif // BINARYDATA_MONSTERTYPEDUNGEONSTORAGE_H
