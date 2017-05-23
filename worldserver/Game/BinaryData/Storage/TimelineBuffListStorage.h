#ifndef BINARYDATA_TIMELINEBUFFLISTSTORAGE_H
#define BINARYDATA_TIMELINEBUFFLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class TimelineBuffListStorage : public BinaryDataStorage<T>
{
public:
    TimelineBuffListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            TimelineBuffListBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_typeId = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_forPlayer = this->_reader->ReadBool();
            entry.m_effectIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for TimelineBuffListStorage";
    }
};

#endif // BINARYDATA_TIMELINEBUFFLISTSTORAGE_H
