#ifndef BINARYDATA_RECYCLEMACHINEINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_RECYCLEMACHINEINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class RecycleMachineInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    RecycleMachineInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            RecycleMachineInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualMruId = this->_reader->ReadInt();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for RecycleMachineInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_RECYCLEMACHINEINTERACTIVEELEMENTPARAMSTORAGE_H
