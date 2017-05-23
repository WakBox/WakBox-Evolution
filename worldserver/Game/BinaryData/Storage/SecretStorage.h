#ifndef BINARYDATA_SECRETSTORAGE_H
#define BINARYDATA_SECRETSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class SecretStorage : public BinaryDataStorage<T>
{
public:
    SecretStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            SecretBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_level = this->_reader->ReadShort();
            entry.m_itemId = this->_reader->ReadShort();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for SecretStorage";
    }
};

#endif // BINARYDATA_SECRETSTORAGE_H
