#ifndef BINARYDATA_HAVENWORLDBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_HAVENWORLDBOARDINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBoardInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBoardInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBoardInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_havenWorldId = this->_reader->ReadShort();
            entry.m_miniOriginCellX = this->_reader->ReadShort();
            entry.m_miniOriginCellY = this->_reader->ReadShort();
            entry.m_miniOriginCellZ = this->_reader->ReadShort();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBoardInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBOARDINTERACTIVEELEMENTPARAMSTORAGE_H
