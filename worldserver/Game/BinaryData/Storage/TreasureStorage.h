#ifndef BINARYDATA_TREASURESTORAGE_H
#define BINARYDATA_TREASURESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class TreasureStorage : public BinaryDataStorage<T>
{
public:
    TreasureStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            TreasureBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_usedItem = this->_reader->ReadInt();
            entry.m_rewardItem = this->_reader->ReadInt();
            entry.m_quantity = this->_reader->ReadShort();
            entry.m_rewardKama = this->_reader->ReadInt();
            entry.m_rewardLootChest = this->_reader->ReadInt();
            entry.m_duration = this->_reader->ReadInt();
            entry.m_criterion = this->_reader->ReadString();
            entry.m_winPercent = this->_reader->ReadFloat();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for TreasureStorage";
    }
};

#endif // BINARYDATA_TREASURESTORAGE_H
