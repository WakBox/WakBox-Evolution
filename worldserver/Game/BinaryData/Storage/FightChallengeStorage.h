#ifndef BINARYDATA_FIGHTCHALLENGESTORAGE_H
#define BINARYDATA_FIGHTCHALLENGESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class FightChallengeStorage : public BinaryDataStorage<T>
{
public:
    FightChallengeStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            FightChallengeBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_dropWeight = this->_reader->ReadInt();
            entry.m_dropCriterion = this->_reader->ReadString();
            entry.m_stateId = this->_reader->ReadInt();
            entry.m_listenedEffectSuccess = this->_reader->ReadInt();
            entry.m_listenedEffectFailure = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_isBase = this->_reader->ReadBool();
            entry.m_incompatibleChallenges = this->_reader->ReadIntArray();
            entry.m_incompatibleMonsters = this->_reader->ReadIntArray();

            qint32 rewardCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < rewardCount; ++i)
            {
                FightChallengeReward reward;

                reward.m_id = this->_reader->ReadInt();
                reward.m_criterion = this->_reader->ReadString();
                reward.m_xpLevel = this->_reader->ReadShort();
                reward.m_dropLevel = this->_reader->ReadShort();

                entry.m_rewards.push_back(reward);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for FightChallengeStorage";
    }
};

#endif // BINARYDATA_FIGHTCHALLENGESTORAGE_H
