#ifndef BINARYDATA_DUNGEONDISPLAYERINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_DUNGEONDISPLAYERINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DungeonDisplayerInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    DungeonDisplayerInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DungeonDisplayerInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_dungeonId = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DungeonDisplayerInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_DUNGEONDISPLAYERINTERACTIVEELEMENTPARAMSTORAGE_H
