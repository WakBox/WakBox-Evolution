#ifndef BINARYDATA_BACKGROUNDINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_BACKGROUNDINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BackgroundInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    BackgroundInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BackgroundInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_visualId = this->_reader->ReadInt();
            entry.m_backgroundFeedback = this->_reader->ReadInt();

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BackgroundInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_BACKGROUNDINTERACTIVEELEMENTPARAMSTORAGE_H
