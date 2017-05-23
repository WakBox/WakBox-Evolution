#ifndef BINARYDATA_ITEMTYPESTORAGE_H
#define BINARYDATA_ITEMTYPESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ItemTypeStorage : public BinaryDataStorage<T>
{
public:
    ItemTypeStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ItemTypeBinaryData entry;

            entry.m_id = this->_reader->ReadShort();
            entry.m_parentId = this->_reader->ReadShort();
            entry.m_visibleInAnimations = this->_reader->ReadBool();
            entry.m_visibleInMarketPlace = this->_reader->ReadBool();
            entry.m_recyclable = this->_reader->ReadBool();
            entry.m_equipmentPosition = this->_reader->ReadStringArray();
            entry.m_disabledEquipementPosition = this->_reader->ReadStringArray();
            entry.m_materialType = this->_reader->ReadShort();
            entry.m_craftIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ItemTypeStorage";
    }
};

#endif // BINARYDATA_ITEMTYPESTORAGE_H
