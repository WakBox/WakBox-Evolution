#ifndef BINARYDATA_COLLECTINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_COLLECTINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CollectInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    CollectInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CollectInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_capacity = this->_reader->ReadShort();
            entry.m_locked = this->_reader->ReadBool();
            entry.m_cashQty = this->_reader->ReadInt();

            qint32 itemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < itemCount; ++i)
            {
                CollectItem collectItem;

                collectItem.m_uid = this->_reader->ReadInt();
                collectItem.m_itemId = this->_reader->ReadInt();
                collectItem.m_qty = this->_reader->ReadInt();

                entry.m_items.push_back(collectItem);
            }


            qint32 actionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < actionCount; ++i)
            {
                CollectAction collectAction;

                collectAction.m_actionId = this->_reader->ReadInt();
                collectAction.m_actionType = this->_reader->ReadInt();
                collectAction.m_params = this->_reader->ReadStringArray();
                collectAction.m_criteria = this->_reader->ReadString();

                entry.m_actions.push_back(collectAction);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CollectInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_COLLECTINTERACTIVEELEMENTPARAMSTORAGE_H
