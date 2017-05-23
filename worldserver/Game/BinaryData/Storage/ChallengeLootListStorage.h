#ifndef BINARYDATA_CHALLENGELOOTLISTSTORAGE_H
#define BINARYDATA_CHALLENGELOOTLISTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ChallengeLootListStorage : public BinaryDataStorage<T>
{
public:
    ChallengeLootListStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ChallengeLootListBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 entrieCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < entrieCount; ++i)
            {
                ChallengeLootEntry challengeLootEntry;

                challengeLootEntry.m_challengeId = this->_reader->ReadInt();
                challengeLootEntry.m_criteria = this->_reader->ReadString();

                entry.m_entries.push_back(challengeLootEntry);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ChallengeLootListStorage";
    }
};

#endif // BINARYDATA_CHALLENGELOOTLISTSTORAGE_H
