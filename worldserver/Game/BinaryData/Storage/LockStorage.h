#ifndef BINARYDATA_LOCKSTORAGE_H
#define BINARYDATA_LOCKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class LockStorage : public BinaryDataStorage<T>
{
public:
    LockStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            LockBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_lockedItemId = this->_reader->ReadInt();
            entry.m_lockValue = this->_reader->ReadInt();
            entry.m_periodDuration = this->_reader->ReadLong();
            entry.m_unlockDate = this->_reader->ReadLong();
            entry.m_availableForCitizensOnly = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for LockStorage";
    }
};

#endif // BINARYDATA_LOCKSTORAGE_H
