#ifndef BINARYDATA_STOOLINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_STOOLINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class StoolInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    StoolInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            StoolInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_criterion = this->_reader->ReadString();
            entry.m_visualId = this->_reader->ReadInt();
            entry.if (buffer.get() != 0) { = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for StoolInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_STOOLINTERACTIVEELEMENTPARAMSTORAGE_H
