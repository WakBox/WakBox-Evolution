#ifndef BINARYDATA_BOATSTORAGE_H
#define BINARYDATA_BOATSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BoatStorage : public BinaryDataStorage<T>
{
public:
    BoatStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BoatBinaryData entry;

            entry.m_boatId = this->_reader->ReadInt();
            entry.m_exitX = this->_reader->ReadInt();
            entry.m_exitY = this->_reader->ReadInt();
            entry.m_exitWorldId = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_uiGfxId = this->_reader->ReadInt();
            entry.m_landmarkTravelType = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BoatStorage";
    }
};

#endif // BINARYDATA_BOATSTORAGE_H
