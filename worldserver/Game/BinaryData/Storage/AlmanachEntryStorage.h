#ifndef BINARYDATA_ALMANACHENTRYSTORAGE_H
#define BINARYDATA_ALMANACHENTRYSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AlmanachEntryStorage : public BinaryDataStorage<T>
{
public:
    AlmanachEntryStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AlmanachEntryBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_scenarioId = this->_reader->ReadInt();
            entry.m_achievementId = this->_reader->ReadInt();
            entry.m_territories = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AlmanachEntryStorage";
    }
};

#endif // BINARYDATA_ALMANACHENTRYSTORAGE_H
