#ifndef BINARYDATA_TRAVELLOADINGSTORAGE_H
#define BINARYDATA_TRAVELLOADINGSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class TravelLoadingStorage : public BinaryDataStorage<T>
{
public:
    TravelLoadingStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            TravelLoadingBinaryData entry;

            entry.m_loadingAnimationName = this->_reader->ReadString();
            entry.m_loadingMinDuration = this->_reader->ReadInt();
            entry.m_loadingFadeInDuration = this->_reader->ReadInt();
            entry.m_loadingFadeOutDuration = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for TravelLoadingStorage";
    }
};

#endif // BINARYDATA_TRAVELLOADINGSTORAGE_H
