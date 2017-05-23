#ifndef BINARYDATA_INSTANCEINTERACTIONLEVELSTORAGE_H
#define BINARYDATA_INSTANCEINTERACTIONLEVELSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class InstanceInteractionLevelStorage : public BinaryDataStorage<T>
{
public:
    InstanceInteractionLevelStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            InstanceInteractionLevelBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_worldId = this->_reader->ReadInt();
            entry.m_subscriptionLevel = this->_reader->ReadInt();
            entry.m_interactionLevel = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for InstanceInteractionLevelStorage";
    }
};

#endif // BINARYDATA_INSTANCEINTERACTIONLEVELSTORAGE_H
