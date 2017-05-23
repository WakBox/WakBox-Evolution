#ifndef BINARYDATA_EFFECTGROUPSTORAGE_H
#define BINARYDATA_EFFECTGROUPSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class EffectGroupStorage : public BinaryDataStorage<T>
{
public:
    EffectGroupStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            EffectGroupBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_effectIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for EffectGroupStorage";
    }
};

#endif // BINARYDATA_EFFECTGROUPSTORAGE_H
