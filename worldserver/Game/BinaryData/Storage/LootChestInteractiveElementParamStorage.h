#ifndef BINARYDATA_LOOTCHESTINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_LOOTCHESTINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class LootChestInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    LootChestInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            LootChestInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_cooldown = this->_reader->ReadInt();
            entry.m_cost = this->_reader->ReadInt();
            entry.m_itemIdCost = this->_reader->ReadInt();
            entry.m_itemQuantityCost = this->_reader->ReadInt();
            entry.m_doConsumeItem = this->_reader->ReadBool();
            entry.m_nbActivation = this->_reader->ReadInt();
            entry.m_distributionDuration = this->_reader->ReadInt();
            entry.m_criteria = this->_reader->ReadString();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for LootChestInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_LOOTCHESTINTERACTIVEELEMENTPARAMSTORAGE_H
