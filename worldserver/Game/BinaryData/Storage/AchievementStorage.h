#ifndef BINARYDATA_ACHIEVEMENTSTORAGE_H
#define BINARYDATA_ACHIEVEMENTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

class AchievementStorage : public BinaryDataStorage
{
public:
    AchievementStorage() : BinaryDataStorage() { }

    void Load()
    {
        qint32 size = m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = m_rows[i];
            SetBufferPosition(row.offset);

            AchievementBinaryData entry;

            entry.m_id = ReadInt();
            entry.m_categoryId = ReadInt();
            entry.m_isVisible = ReadBool();
            entry.m_notifyOnPass = ReadBool();
            entry.m_isActive = ReadBool();
            entry.m_criterion = ReadString();
            entry.m_activationCriterion = ReadString();

            qint32 goalCount = ReadInt();

            for (qint32 i = 0; i < goalCount; ++i)
            {
                AchievementGoal achievementGoal;

                achievementGoal.m_id = ReadInt();
                achievementGoal.m_feedback = ReadBool();
                achievementGoal.m_hasPositionFeedback = ReadBool();
                achievementGoal.m_positionX = ReadShort();
                achievementGoal.m_positionY = ReadShort();
                achievementGoal.m_positionZ = ReadShort();
                achievementGoal.m_positionWorldId = ReadShort();
                qint32 vlistenerCount = ReadInt();

                for (qint32 j = 0; j < vlistenerCount; ++j)
                {
                    AchievementVariableListener achievementVariableListener;

                    achievementVariableListener.m_id = ReadInt();
                    achievementVariableListener.m_successCriterion = ReadString();
                    achievementVariableListener.m_variableIds = ReadIntArray();

                    achievementGoal.m_vlisteners.push_back(achievementVariableListener);
                }

                entry.m_goals.push_back(achievementGoal);
            }


            qint32 rewardCount = ReadInt();

            for (qint32 i = 0; i < rewardCount; ++i)
            {
                AchievementReward achievementReward;

                achievementReward.m_id = ReadInt();
                achievementReward.m_type = ReadInt();
                achievementReward.m_params = ReadIntArray();

                entry.m_rewards.push_back(achievementReward);
            }

            entry.m_duration = ReadInt();
            entry.m_cooldown = ReadInt();
            entry.m_shareable = ReadBool();
            entry.m_repeatable = ReadBool();
            entry.m_needsUserAccept = ReadBool();
            entry.m_recommandedLevel = ReadInt();
            entry.m_recommandedPlayers = ReadInt();
            entry.m_followable = ReadBool();
            entry.m_displayOnActivationDelay = ReadInt();
            entry.m_periodStartTime = ReadLong();
            entry.m_period = ReadLong();
            entry.m_autoCompass = ReadBool();
            entry.m_gfxId = ReadInt();
            entry.m_isMercenary = ReadBool();
            entry.m_mercenaryItemId = ReadInt();
            entry.m_mercenaryRank = ReadByte();
            entry.m_order = ReadInt();

            m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << m_entries.size() << " entries for AchievementStorage";
    }

private:
    QMap<qint32, AchievementBinaryData> m_entries;
};

#endif // BINARYDATA_ACHIEVEMENTSTORAGE_H
