#ifndef BINARYDATA_TELEPORTERSTORAGE_H
#define BINARYDATA_TELEPORTERSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class TeleporterStorage : public BinaryDataStorage<T>
{
public:
    TeleporterStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            TeleporterBinaryData entry;

            entry.m_teleporterId = this->_reader->ReadInt();
            entry.m_lockId = this->_reader->ReadInt();

            qint32 destinationCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < destinationCount; ++i)
            {
                Destination destination;

                destination.m_destinationId = this->_reader->ReadInt();
                destination.m_x = this->_reader->ReadInt();
                destination.m_y = this->_reader->ReadInt();
                destination.m_z = this->_reader->ReadInt();
                destination.m_worldId = this->_reader->ReadInt();
                destination.m_direction = this->_reader->ReadByte();
                destination.m_criteria = this->_reader->ReadString();
                destination.m_visualId = this->_reader->ReadInt();
                destination.m_apsId = this->_reader->ReadInt();
                destination.m_delay = this->_reader->ReadShort();
                destination.m_itemConsumed = this->_reader->ReadInt();
                destination.m_itemQuantity = this->_reader->ReadShort();
                destination.m_kamaCost = this->_reader->ReadShort();
                destination.m_doConsumeItem = this->_reader->ReadBool();
                destination.m_isInvisible = this->_reader->ReadBool();
                destination.m_loadingAnimationName = this->_reader->ReadString();
                destination.m_loadingMinDuration = this->_reader->ReadInt();
                destination.m_loadingFadeInDuration = this->_reader->ReadInt();
                destination.m_loadingFadeOutDuration = this->_reader->ReadInt();

                entry.m_destinations.push_back(destination);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for TeleporterStorage";
    }
};

#endif // BINARYDATA_TELEPORTERSTORAGE_H
