#ifndef BINARYDATA_DOORINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_DOORINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DoorInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    DoorInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DoorInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_consumeItem = this->_reader->ReadBool();
            entry.m_itemNeeded = this->_reader->ReadInt();
            entry.m_kamaCost = this->_reader->ReadInt();
            entry.m_criterion = this->_reader->ReadString();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DoorInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_DOORINTERACTIVEELEMENTPARAMSTORAGE_H
