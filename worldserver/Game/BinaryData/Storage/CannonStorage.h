#ifndef BINARYDATA_CANNONSTORAGE_H
#define BINARYDATA_CANNONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CannonStorage : public BinaryDataStorage<T>
{
public:
    CannonStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CannonBinaryData entry;

            entry.m_cannonId = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_uiGfxId = this->_reader->ReadInt();
            entry.m_landmarkTravelType = this->_reader->ReadByte();
            entry.m_itemId = this->_reader->ReadInt();
            entry.m_itemQty = this->_reader->ReadInt();

            qint32 linkCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < linkCount; ++i)
            {
                Link link;

                link.m_id = this->_reader->ReadInt();
                link.m_exitX = this->_reader->ReadInt();
                link.m_exitY = this->_reader->ReadInt();
                link.m_exitWorldId = this->_reader->ReadInt();
                link.m_dropWeight = this->_reader->ReadInt();
                link.m_criteria = this->_reader->ReadString();

                qint8 hasTravelLoading = this->_reader->ReadByte();
                if (hasTravelLoading != 0)
                {
                    link.m_loading.m_loadingAnimationName = this->_reader->ReadString();
                    link.m_loading.m_loadingMinDuration = this->_reader->ReadInt();
                    link.m_loading.m_loadingFadeInDuration = this->_reader->ReadInt();
                    link.m_loading.m_loadingFadeOutDuration = this->_reader->ReadInt();
                }

                entry.m_links.push_back(link);
            }

            this->m_entries[entry.m_cannonId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CannonStorage";
    }
};

#endif // BINARYDATA_CANNONSTORAGE_H
