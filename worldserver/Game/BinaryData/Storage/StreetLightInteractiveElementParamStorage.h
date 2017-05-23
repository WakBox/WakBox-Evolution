#ifndef BINARYDATA_STREETLIGHTINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_STREETLIGHTINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class StreetLightInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    StreetLightInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            StreetLightInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_color = this->_reader->ReadInt();
            entry.m_range = this->_reader->ReadFloat();
            entry.m_apsId = this->_reader->ReadInt();
            entry.m_activeOnlyInNight = this->_reader->ReadBool();
            entry.m_ignitionVisualId = this->_reader->ReadInt();
            entry.m_ignitionUseObject = this->_reader->ReadBool();
            entry.m_ignitionDuration = this->_reader->ReadInt();
            entry.m_extinctionVisualId = this->_reader->ReadInt();
            entry.m_extinctionUseObject = this->_reader->ReadBool();
            entry.m_extinctionDuration = this->_reader->ReadInt();
            entry.if (buffer.get() != 0) { = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for StreetLightInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_STREETLIGHTINTERACTIVEELEMENTPARAMSTORAGE_H
