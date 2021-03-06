#ifndef BINARYDATA_EQUIPABLEDUMMYINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_EQUIPABLEDUMMYINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class EquipableDummyInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    EquipableDummyInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            EquipableDummyInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_animName = this->_reader->ReadString();
            entry.m_sex = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for EquipableDummyInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_EQUIPABLEDUMMYINTERACTIVEELEMENTPARAMSTORAGE_H
