#ifndef BINARYDATA_BOARDINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_BOARDINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BoardInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    BoardInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BoardInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BoardInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_BOARDINTERACTIVEELEMENTPARAMSTORAGE_H
