#ifndef BINARYDATA_MAGICRAFTLOOTLISTSTORAGE_H
#define BINARYDATA_MAGICRAFTLOOTLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MagiCraftLootListStorage : public BinaryDataStorage<T>
{
public:
    MagiCraftLootListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MagiCraftLootListBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_gemType = this->_reader->ReadByte();

            qint32 entrieCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < entrieCount; ++i)
            {
                MagiCraftLootEntry lootEntry;

                lootEntry.m_itemId = this->_reader->ReadInt();

                entry.m_entries.push_back(lootEntry);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MagiCraftLootListStorage";
    }
};

#endif // BINARYDATA_MAGICRAFTLOOTLISTSTORAGE_H
