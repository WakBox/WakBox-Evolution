#ifndef BINARYDATA_MONSTERTYPERELASHIONSHIPSTORAGE_H
#define BINARYDATA_MONSTERTYPERELASHIONSHIPSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MonsterTypeRelashionshipStorage : public BinaryDataStorage<T>
{
public:
    MonsterTypeRelashionshipStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MonsterTypeRelashionshipBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_familyFrom = this->_reader->ReadInt();
            entry.m_familyTo = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MonsterTypeRelashionshipStorage";
    }
};

#endif // BINARYDATA_MONSTERTYPERELASHIONSHIPSTORAGE_H
