#ifndef BINARYDATA_CRAFTSTORAGE_H
#define BINARYDATA_CRAFTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CraftStorage : public BinaryDataStorage<T>
{
public:
    CraftStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CraftBinaryData entry;

            entry.m_craftId = this->_reader->ReadInt();
            entry.m_bookItemId = this->_reader->ReadInt();
            entry.m_xpFactor = this->_reader->ReadFloat();
            entry.m_innate = this->_reader->ReadBool();
            entry.m_conceptualCraft = this->_reader->ReadBool();
            entry.m_hiddenCraft = this->_reader->ReadBool();

            this->m_entries[entry.m_craftId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CraftStorage";
    }
};

#endif // BINARYDATA_CRAFTSTORAGE_H
