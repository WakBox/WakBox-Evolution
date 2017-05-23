#ifndef BINARYDATA_ITEMSETSTORAGE_H
#define BINARYDATA_ITEMSETSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ItemSetStorage : public BinaryDataStorage<T>
{
public:
    ItemSetStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ItemSetBinaryData entry;

            entry.m_id = this->_reader->ReadShort();
            entry.m_linkedItemReferenceId = this->_reader->ReadInt();
            entry.m_itemsId = this->_reader->ReadIntArray();

            qint32 effectIdsByPartCountCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < effectIdsByPartCountCount; ++i)
            {
                TIntObjectHashMap<int tIntObjectHashMap<int;


                entry.m_effectIdsByPartCount.push_back(tIntObjectHashMap<int);
            }


            qint32 effectIdsByPartCountKey = this->_reader->ReadInt();

            for (qint32 i = 0; i < effectIdsByPartCountKey; ++i)
            {
                ReadIntArray(); readIntArray();;


                entry.effectIdsByPartCountValue.push_back(readIntArray(););
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ItemSetStorage";
    }
};

#endif // BINARYDATA_ITEMSETSTORAGE_H
