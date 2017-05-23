#ifndef BINARYDATA_EMOTESTORAGE_H
#define BINARYDATA_EMOTESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class EmoteStorage : public BinaryDataStorage<T>
{
public:
    EmoteStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            EmoteBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadShort();
            entry.m_cmd = this->_reader->ReadString();
            entry.m_needTarget = this->_reader->ReadBool();
            entry.m_moveToTarget = this->_reader->ReadBool();
            entry.m_infiniteDuration = this->_reader->ReadBool();
            entry.m_isMusical = this->_reader->ReadBool();
            entry.m_scriptParams = this->_reader->ReadStringArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for EmoteStorage";
    }
};

#endif // BINARYDATA_EMOTESTORAGE_H
