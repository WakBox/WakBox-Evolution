#ifndef BINARYDATA_ARCADEDUNGEONSTORAGE_H
#define BINARYDATA_ARCADEDUNGEONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ArcadeDungeonStorage : public BinaryDataStorage<T>
{
public:
    ArcadeDungeonStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ArcadeDungeonBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_worldId = this->_reader->ReadShort();

            qint32 challengeCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < challengeCount; ++i)
            {
                Challenge challenge;

                challenge.m_id = this->_reader->ReadInt();
                challenge.m_ratio = this->_reader->ReadFloat();

                entry.m_challenges.push_back(challenge);
            }


            qint32 rewardsListCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < rewardsListCount; ++i)
            {
                RewardList rewardList;

                rewardList.m_id = this->_reader->ReadInt();
                rewardList.m_levelOrder = this->_reader->ReadInt();
                qint32 rewardCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < rewardCount; ++j)
                {
                    Reward reward;

                    reward.m_scoreMin = this->_reader->ReadInt();
                    reward.m_itemId = this->_reader->ReadInt();
                    reward.m_xpValue = this->_reader->ReadInt();
                    reward.m_rankNeeded = this->_reader->ReadByte();

                    rewardList.m_rewards.push_back(reward);
                }

                entry.m_rewardsList.push_back(rewardList);
            }


            qint32 rankCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < rankCount; ++i)
            {
                RankDef rankDef;

                rankDef.m_levelOrder = this->_reader->ReadInt();
                rankDef.m_scoreMinD = this->_reader->ReadInt();
                rankDef.m_scoreMinC = this->_reader->ReadInt();
                rankDef.m_scoreMinB = this->_reader->ReadInt();
                rankDef.m_scoreMinA = this->_reader->ReadInt();

                entry.m_ranks.push_back(rankDef);
            }

            entry.m_scoreRoundBase = this->_reader->ReadInt();
            entry.m_scoreRoundIncr = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ArcadeDungeonStorage";
    }
};

#endif // BINARYDATA_ARCADEDUNGEONSTORAGE_H
