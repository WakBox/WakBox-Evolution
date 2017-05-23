#ifndef BINARYDATA_CLIENTEVENTSTORAGE_H
#define BINARYDATA_CLIENTEVENTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ClientEventStorage : public BinaryDataStorage<T>
{
public:
    ClientEventStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ClientEventBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadInt();
            entry.m_dropRate = this->_reader->ReadShort();
            entry.m_maxCount = this->_reader->ReadShort();
            entry.m_criterion = this->_reader->ReadString();
            entry.m_filters = this->_reader->ReadStringArray();
            entry.m_activeOnStart = this->_reader->ReadBool();

            qint32 actionGroupCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < actionGroupCount; ++i)
            {
                EventActionGroup eventActionGroup;

                eventActionGroup.m_id = this->_reader->ReadInt();
                eventActionGroup.m_dropRate = this->_reader->ReadShort();
                eventActionGroup.m_criterion = this->_reader->ReadString();
                qint32 actionCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < actionCount; ++j)
                {
                    EventAction eventAction;

                    eventAction.m_id = this->_reader->ReadInt();
                    eventAction.m_type = this->_reader->ReadInt();
                    eventAction.m_params = this->_reader->ReadStringArray();

                    eventActionGroup.m_actions.push_back(eventAction);
                }

                entry.m_actionGroups.push_back(eventActionGroup);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ClientEventStorage";
    }
};

#endif // BINARYDATA_CLIENTEVENTSTORAGE_H
