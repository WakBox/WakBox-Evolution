#ifndef BINARYDATA_ACHIEVEMENTSTORAGE_H
#define BINARYDATA_ACHIEVEMENTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AchievementStorage : public BinaryDataStorage<T>
{
public:
    AchievementStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AchievementBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_isVisible = this->_reader->ReadBool();
            entry.m_notifyOnPass = this->_reader->ReadBool();
            entry.m_isActive = this->_reader->ReadBool();
            entry.m_criterion = this->_reader->ReadString();
            entry.m_activationCriterion = this->_reader->ReadString();

            qint32 goalCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < goalCount; ++i)
            {
                AchievementGoal achievementGoal;

                achievementGoal.m_id = this->_reader->ReadInt();
                achievementGoal.m_feedback = this->_reader->ReadBool();
                achievementGoal.m_hasPositionFeedback = this->_reader->ReadBool();
                achievementGoal.m_positionX = this->_reader->ReadShort();
                achievementGoal.m_positionY = this->_reader->ReadShort();
                achievementGoal.m_positionZ = this->_reader->ReadShort();
                achievementGoal.m_positionWorldId = this->_reader->ReadShort();
                qint32 vlistenerCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < vlistenerCount; ++j)
                {
                    AchievementVariableListener achievementVariableListener;

                    achievementVariableListener.m_id = this->_reader->ReadInt();
                    achievementVariableListener.m_successCriterion = this->_reader->ReadString();
                    achievementVariableListener.m_variableIds = this->_reader->ReadIntArray();

                    achievementGoal.m_vlisteners.push_back(achievementVariableListener);
                }

                entry.m_goals.push_back(achievementGoal);
            }


            qint32 rewardCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < rewardCount; ++i)
            {
                AchievementReward achievementReward;

                achievementReward.m_id = this->_reader->ReadInt();
                achievementReward.m_type = this->_reader->ReadInt();
                achievementReward.m_params = this->_reader->ReadIntArray();

                entry.m_rewards.push_back(achievementReward);
            }

            entry.m_duration = this->_reader->ReadInt();
            entry.m_cooldown = this->_reader->ReadInt();
            entry.m_shareable = this->_reader->ReadBool();
            entry.m_repeatable = this->_reader->ReadBool();
            entry.m_needsUserAccept = this->_reader->ReadBool();
            entry.m_recommandedLevel = this->_reader->ReadInt();
            entry.m_recommandedPlayers = this->_reader->ReadInt();
            entry.m_followable = this->_reader->ReadBool();
            entry.m_displayOnActivationDelay = this->_reader->ReadInt();
            entry.m_periodStartTime = this->_reader->ReadLong();
            entry.m_period = this->_reader->ReadLong();
            entry.m_autoCompass = this->_reader->ReadBool();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_isMercenary = this->_reader->ReadBool();
            entry.m_mercenaryItemId = this->_reader->ReadInt();
            entry.m_mercenaryRank = this->_reader->ReadByte();
            entry.m_order = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = &entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AchievementStorage";
    }
};

#endif // BINARYDATA_ACHIEVEMENTSTORAGE_H
