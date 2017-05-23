#ifndef BINARYDATA_LIGHTLOOTLISTSTORAGE_H
#define BINARYDATA_LIGHTLOOTLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class LightLootListStorage : public BinaryDataStorage<T>
{
public:
    LightLootListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            LightLootListBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 entrieCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < entrieCount; ++i)
            {
                LootEntry lootEntry;

                lootEntry.m_itemId = this->_reader->ReadInt();
                lootEntry.m_quantity = this->_reader->ReadShort();
                lootEntry.m_quantityPerItem = this->_reader->ReadShort();

                entry.m_entries.push_back(lootEntry);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for LightLootListStorage";
    }
};

#endif // BINARYDATA_LIGHTLOOTLISTSTORAGE_H
