#ifndef BINARYDATA_KROSMOZFIGURESTORAGE_H
#define BINARYDATA_KROSMOZFIGURESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class KrosmozFigureStorage : public BinaryDataStorage<T>
{
public:
    KrosmozFigureStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            KrosmozFigureBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_year = this->_reader->ReadInt();
            entry.m_addon = this->_reader->ReadInt();
            entry.m_season = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for KrosmozFigureStorage";
    }
};

#endif // BINARYDATA_KROSMOZFIGURESTORAGE_H
