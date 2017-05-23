#ifndef BINARYDATA_ITEMSTORAGE_H
#define BINARYDATA_ITEMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ItemStorage : public BinaryDataStorage<T>
{
public:
    ItemStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ItemBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_metaId = this->_reader->ReadInt();
            entry.m_itemSetId = this->_reader->ReadShort();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_femaleGfxId = this->_reader->ReadInt();
            entry.m_floorGfxId = this->_reader->ReadInt();
            entry.m_level = this->_reader->ReadShort();
            entry.m_criteria = this->_reader->ReadStringArray();
            entry.m_itemTypeId = this->_reader->ReadInt();
            entry.m_maxStackHeight = this->_reader->ReadShort();
            entry.m_useCostAP = this->_reader->ReadByte();
            entry.m_useCostMP = this->_reader->ReadByte();
            entry.m_useCostFP = this->_reader->ReadByte();
            entry.m_useRangeMin = this->_reader->ReadInt();
            entry.m_useRangeMax = this->_reader->ReadInt();
            entry.m_useTestFreeCell = this->_reader->ReadBool();
            entry.m_useTestNotBorderCell = this->_reader->ReadBool();
            entry.m_useTestLos = this->_reader->ReadBool();
            entry.m_useTestOnlyLine = this->_reader->ReadBool();
            entry.m_itemRarity = this->_reader->ReadShort();
            entry.m_itemBindType = this->_reader->ReadByte();
            entry.m_generationType = this->_reader->ReadString();
            entry.m_itemProperties = this->_reader->ReadIntArray();
            entry.m_itemActionVisual = this->_reader->ReadByte();
            entry.m_worldUsageTarget = this->_reader->ReadByte();
            entry.m_gemElementType = this->_reader->ReadByte();
            entry.m_gemNum = this->_reader->ReadByte();
            entry.m_effectIds = this->_reader->ReadIntArray();

            qint32 actionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < actionCount; ++i)
            {
                ItemAction itemAction;

                itemAction.m_actionId = this->_reader->ReadInt();
                itemAction.m_actionTypeId = this->_reader->ReadInt();
                itemAction.m_consumeItemOnAction = this->_reader->ReadBool();
                itemAction.m_clientOnly = this->_reader->ReadBool();
                itemAction.m_stopMovement = this->_reader->ReadBool();
                itemAction.m_hasScript = this->_reader->ReadBool();
                itemAction.m_criteria = this->_reader->ReadString();
                itemAction.m_actionParams = this->_reader->ReadStringArray();
                itemAction.m_actionScriptParams = this->_reader->ReadStringArray();

                entry.m_actions.push_back(itemAction);
            }

            entry.m_subMetaIds = this->_reader->ReadIntArray();
            entry.m_gemSlots = this->_reader->ReadByteArray();
            entry.m_gemSlotType = this->_reader->ReadByteArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ItemStorage";
    }
};

#endif // BINARYDATA_ITEMSTORAGE_H
