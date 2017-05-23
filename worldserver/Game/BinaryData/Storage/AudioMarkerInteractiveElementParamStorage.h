#ifndef BINARYDATA_AUDIOMARKERINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_AUDIOMARKERINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AudioMarkerInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    AudioMarkerInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AudioMarkerInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_audioMarkerTypeId = this->_reader->ReadInt();
            entry.m_isLocalized = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AudioMarkerInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_AUDIOMARKERINTERACTIVEELEMENTPARAMSTORAGE_H
