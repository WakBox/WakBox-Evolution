#ifndef BINARYDATA_KROSMOZGAMEBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_KROSMOZGAMEBOARDINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class KrosmozGameBoardInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    KrosmozGameBoardInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            KrosmozGameBoardInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_gameId = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for KrosmozGameBoardInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_KROSMOZGAMEBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
