#ifndef BINARYDATA_HAVENBAGMODELVIEWSTORAGE_H
#define BINARYDATA_HAVENBAGMODELVIEWSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenBagModelViewStorage : public BinaryDataStorage<T>
{
public:
    HavenBagModelViewStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenBagModelViewBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_restrictionWorld = this->_reader->ReadBool();
            entry.m_restrictionMarket = this->_reader->ReadBool();
            entry.m_backgroundMapId = this->_reader->ReadInt();
            entry.m_innate = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenBagModelViewStorage";
    }
};

#endif // BINARYDATA_HAVENBAGMODELVIEWSTORAGE_H
