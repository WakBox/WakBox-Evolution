#ifndef BINARYDATA_NATIONCOLORSSTORAGE_H
#define BINARYDATA_NATIONCOLORSSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class NationColorsStorage : public BinaryDataStorage<T>
{
public:
    NationColorsStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            NationColorsBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_color = this->_reader->ReadString();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for NationColorsStorage";
    }
};

#endif // BINARYDATA_NATIONCOLORSSTORAGE_H
