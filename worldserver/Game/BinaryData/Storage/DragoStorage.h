#ifndef BINARYDATA_DRAGOSTORAGE_H
#define BINARYDATA_DRAGOSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class DragoStorage : public BinaryDataStorage<T>
{
public:
    DragoStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            DragoBinaryData entry;

            entry.m_dragoId = this->_reader->ReadInt();
            entry.m_exitX = this->_reader->ReadInt();
            entry.m_exitY = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_uiGfxId = this->_reader->ReadInt();
            entry.m_dragoCriterion = this->_reader->ReadString();
            entry.m_landmarkTravelType = this->_reader->ReadByte();

            qint8 hasTravelLoading = this->_reader->ReadByte();
            if (hasTravelLoading != 0)
            {
                entry.m_loading.m_loadingAnimationName = this->_reader->ReadString();
                entry.m_loading.m_loadingMinDuration = this->_reader->ReadInt();
                entry.m_loading.m_loadingFadeInDuration = this->_reader->ReadInt();
                entry.m_loading.m_loadingFadeOutDuration = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_dragoId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for DragoStorage";
    }
};

#endif // BINARYDATA_DRAGOSTORAGE_H
