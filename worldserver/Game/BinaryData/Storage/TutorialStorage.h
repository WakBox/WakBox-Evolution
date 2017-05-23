#ifndef BINARYDATA_TUTORIALSTORAGE_H
#define BINARYDATA_TUTORIALSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class TutorialStorage : public BinaryDataStorage<T>
{
public:
    TutorialStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            TutorialBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 eventIdCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < eventIdCount; ++i)
            {
                Event event;

                event.m_eventId = this->_reader->ReadInt();

                entry.m_eventIds.push_back(event);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for TutorialStorage";
    }
};

#endif // BINARYDATA_TUTORIALSTORAGE_H
