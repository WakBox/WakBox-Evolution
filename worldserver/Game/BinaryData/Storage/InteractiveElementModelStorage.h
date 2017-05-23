#ifndef BINARYDATA_INTERACTIVEELEMENTMODELSTORAGE_H
#define BINARYDATA_INTERACTIVEELEMENTMODELSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class InteractiveElementModelStorage : public BinaryDataStorage<T>
{
public:
    InteractiveElementModelStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            InteractiveElementModelBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadShort();
            entry.m_gfx = this->_reader->ReadInt();
            entry.m_color = this->_reader->ReadInt();
            entry.m_height = this->_reader->ReadByte();
            entry.m_particleId = this->_reader->ReadInt();
            entry.m_particleOffsetZ = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for InteractiveElementModelStorage";
    }
};

#endif // BINARYDATA_INTERACTIVEELEMENTMODELSTORAGE_H
