#ifndef BINARYDATA_MARKETBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_MARKETBOARDINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MarketBoardInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    MarketBoardInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MarketBoardInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualMruId = this->_reader->ReadInt();
            entry.m_marketId = this->_reader->ReadInt();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MarketBoardInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_MARKETBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
