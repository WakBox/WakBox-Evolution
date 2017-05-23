#ifndef BINARYDATA_FIGHTCHALLENGEMONSTERSTORAGE_H
#define BINARYDATA_FIGHTCHALLENGEMONSTERSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class FightChallengeMonsterStorage : public BinaryDataStorage<T>
{
public:
    FightChallengeMonsterStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            FightChallengeMonsterBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_randomRolls = this->_reader->ReadShort();
            entry.m_forcedRolls = this->_reader->ReadShort();
            entry.m_forcedChallenges = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for FightChallengeMonsterStorage";
    }
};

#endif // BINARYDATA_FIGHTCHALLENGEMONSTERSTORAGE_H
