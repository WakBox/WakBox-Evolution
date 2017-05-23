#ifndef BINARYDATA_RESOURCESTORAGE_H
#define BINARYDATA_RESOURCESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ResourceStorage : public BinaryDataStorage<T>
{
public:
    ResourceStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ResourceBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadInt();
            entry.m_idealRainMin = this->_reader->ReadShort();
            entry.m_idealRainMax = this->_reader->ReadShort();
            entry.m_idealTemperatureMin = this->_reader->ReadShort();
            entry.m_idealTemperatureMax = this->_reader->ReadShort();
            entry.m_isBlocking = this->_reader->ReadBool();
            entry.m_useBigChallengeAps = this->_reader->ReadBool();
            entry.m_isMonsterEmbryo = this->_reader->ReadBool();
            entry.m_monsterStepHatching = this->_reader->ReadShort();
            entry.m_properties = this->_reader->ReadIntArray();
            entry.m_monsterFamilies = this->_reader->ReadIntArray();

            qint32 stepCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < stepCount; ++i)
            {
                ResourceStep resourceStep;

                resourceStep.m_index = this->_reader->ReadInt();
                qint32 actionCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < actionCount; ++j)
                {
                    ResourceStepAction resourceStepAction;

                    resourceStepAction.m_id = this->_reader->ReadInt();
                    resourceStepAction.m_skillId = this->_reader->ReadInt();
                    resourceStepAction.m_resourceNextIndex = this->_reader->ReadInt();
                    resourceStepAction.m_skillLevelRequired = this->_reader->ReadInt();
                    resourceStepAction.m_skillSimultaneousPlayer = this->_reader->ReadInt();
                    resourceStepAction.m_skillVisualFeedbackId = this->_reader->ReadInt();
                    resourceStepAction.m_duration = this->_reader->ReadInt();
                    resourceStepAction.m_consumableId = this->_reader->ReadInt();
                    resourceStepAction.m_gfxId = this->_reader->ReadInt();
                    resourceStepAction.m_criteria = this->_reader->ReadString();
                    resourceStepAction.m_collectLootListId = this->_reader->ReadInt();
                    resourceStepAction.m_collectItemId = this->_reader->ReadInt();
                    resourceStepAction.m_lootItems = this->_reader->ReadIntArray();
                    resourceStepAction.m_mruOrder = this->_reader->ReadInt();
                    resourceStepAction.m_displayInCraftDialog = this->_reader->ReadBool();

                    resourceStep.m_actions.push_back(resourceStepAction);
                }

                resourceStep.m_sizeCategoryId = this->_reader->ReadInt();
                resourceStep.m_lightRadius = this->_reader->ReadInt();
                resourceStep.m_lightColor = this->_reader->ReadInt();
                resourceStep.m_apsId = this->_reader->ReadInt();
                resourceStep.m_apsPosZ = this->_reader->ReadInt();

                entry.m_steps.push_back(resourceStep);
            }

            entry.m_height = this->_reader->ReadShort();
            entry.m_iconGfxId = this->_reader->ReadInt();

            qint32 gfxIdCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < gfxIdCount; ++i)
            {
                qint32 gfxIdKey = this->_reader->ReadInt();
                QList<qint32> gfxIdValue = this->_reader->ReadIntArray();

                entry.m_gfxIds.insert(gfxIdKey, gfxIdValue);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ResourceStorage";
    }
};

#endif // BINARYDATA_RESOURCESTORAGE_H
