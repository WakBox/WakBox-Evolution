#ifndef BINARYDATA_KROSMOZGAMECOLLECTIONINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_KROSMOZGAMECOLLECTIONINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class KrosmozGameCollectionInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    KrosmozGameCollectionInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            KrosmozGameCollectionInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_gameId = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for KrosmozGameCollectionInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_KROSMOZGAMECOLLECTIONINTERACTIVEELEMENTPARAMSTORAGE_H
