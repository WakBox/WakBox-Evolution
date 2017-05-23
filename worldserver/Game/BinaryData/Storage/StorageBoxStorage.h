#ifndef BINARYDATA_STORAGEBOXSTORAGE_H
#define BINARYDATA_STORAGEBOXSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class StorageBoxStorage : public BinaryDataStorage<T>
{
public:
    StorageBoxStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            StorageBoxBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            qint32 compartmentCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < compartmentCount; ++i)
            {
                Compartment compartment;

                compartment.m_uid = this->_reader->ReadInt();
                compartment.m_boxId = this->_reader->ReadInt();
                compartment.m_unlockItemId = this->_reader->ReadInt();
                compartment.m_capacity = this->_reader->ReadByte();
                compartment.m_compartmentOrder = this->_reader->ReadInt();

                entry.m_compartments.push_back(compartment);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for StorageBoxStorage";
    }
};

#endif // BINARYDATA_STORAGEBOXSTORAGE_H
