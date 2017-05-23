#ifndef BINARYDATA_BOOKCASEINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_BOOKCASEINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BookcaseInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    BookcaseInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BookcaseInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_size = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BookcaseInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_BOOKCASEINTERACTIVEELEMENTPARAMSTORAGE_H
