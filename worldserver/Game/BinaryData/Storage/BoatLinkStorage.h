#ifndef BINARYDATA_BOATLINKSTORAGE_H
#define BINARYDATA_BOATLINKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BoatLinkStorage : public BinaryDataStorage<T>
{
public:
    BoatLinkStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BoatLinkBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_start = this->_reader->ReadInt();
            entry.m_end = this->_reader->ReadInt();
            entry.m_cost = this->_reader->ReadInt();
            entry.m_criteria = this->_reader->ReadString();
            entry.m_criteriaDisplay = this->_reader->ReadString();
            entry.m_needsToPayEverytime = this->_reader->ReadBool();

            entry.m_loading.m_loadingAnimationName = this->_reader->ReadString();
            entry.m_loading.m_loadingMinDuration = this->_reader->ReadInt();
            entry.m_loading.m_loadingFadeInDuration = this->_reader->ReadInt();
            entry.m_loading.m_loadingFadeOutDuration = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BoatLinkStorage";
    }
};

#endif // BINARYDATA_BOATLINKSTORAGE_H
