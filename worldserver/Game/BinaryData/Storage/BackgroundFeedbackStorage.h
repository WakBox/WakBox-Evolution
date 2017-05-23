#ifndef BINARYDATA_BACKGROUNDFEEDBACKSTORAGE_H
#define BINARYDATA_BACKGROUNDFEEDBACKSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class BackgroundFeedbackStorage : public BinaryDataStorage<T>
{
public:
    BackgroundFeedbackStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            BackgroundFeedbackBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadShort();

            qint32 pageCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < pageCount; ++i)
            {
                Page page;

                page.m_id = this->_reader->ReadInt();
                page.m_order = this->_reader->ReadShort();
                page.m_template = this->_reader->ReadShort();
                page.m_imageId = this->_reader->ReadInt();

                entry.m_pages.push_back(page);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for BackgroundFeedbackStorage";
    }
};

#endif // BINARYDATA_BACKGROUNDFEEDBACKSTORAGE_H
