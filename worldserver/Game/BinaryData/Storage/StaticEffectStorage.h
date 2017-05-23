#ifndef BINARYDATA_STATICEFFECTSTORAGE_H
#define BINARYDATA_STATICEFFECTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class StaticEffectStorage : public BinaryDataStorage<T>
{
public:
    StaticEffectStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            StaticEffectBinaryData entry;

            entry.m_effectId = this->_reader->ReadInt();
            entry.m_actionId = this->_reader->ReadInt();
            entry.m_parentId = this->_reader->ReadInt();
            entry.m_areaOrderingMethod = this->_reader->ReadShort();
            entry.m_areaSize = this->_reader->ReadIntArray();
            entry.m_areaShape = this->_reader->ReadShort();
            entry.m_emptyCellsAreaOrderingMethod = this->_reader->ReadShort();
            entry.m_emptyCellsAreaSize = this->_reader->ReadIntArray();
            entry.m_emptyCellsAreaShape = this->_reader->ReadShort();
            entry.m_triggersBeforeComputation = this->_reader->ReadIntArray();
            entry.m_triggersBeforeExecution = this->_reader->ReadIntArray();
            entry.m_triggersForUnapplication = this->_reader->ReadIntArray();
            entry.m_triggersAfterExecution = this->_reader->ReadIntArray();
            entry.m_triggersAfterAllExecutions = this->_reader->ReadIntArray();
            entry.m_triggersNotRelatedToExecutions = this->_reader->ReadIntArray();
            entry.m_triggersAdditionnal = this->_reader->ReadIntArray();
            entry.m_criticalState = this->_reader->ReadString();
            entry.m_targetValidator = this->_reader->ReadLongArray();
            entry.m_affectedByLocalisation = this->_reader->ReadBool();
            entry.m_durationBase = this->_reader->ReadInt();
            entry.m_durationInc = this->_reader->ReadFloat();
            entry.m_endsAtEndOfTurn = this->_reader->ReadBool();
            entry.m_isDurationInFullTurns = this->_reader->ReadBool();
            entry.m_applyDelayBase = this->_reader->ReadShort();
            entry.m_applyDelayIncrement = this->_reader->ReadFloat();
            entry.m_params = this->_reader->ReadFloatArray();
            entry.m_probabilityBase = this->_reader->ReadFloat();
            entry.m_probabilityInc = this->_reader->ReadFloat();
            entry.m_triggerListenerType = this->_reader->ReadByte();
            entry.m_triggerTargetType = this->_reader->ReadByte();
            entry.m_triggerCasterType = this->_reader->ReadByte();
            entry.m_storeOnSelf = this->_reader->ReadBool();
            entry.m_maxExecution = this->_reader->ReadShort();
            entry.m_maxExecutionIncr = this->_reader->ReadFloat();
            entry.m_maxTargetCount = this->_reader->ReadByte();
            entry.m_isFightEffect = this->_reader->ReadBool();
            entry.m_hmiAction = this->_reader->ReadString();
            entry.m_containerMinLevel = this->_reader->ReadShort();
            entry.m_containerMaxLevel = this->_reader->ReadShort();
            entry.m_effectCriterion = this->_reader->ReadString();
            entry.m_effectParentType = this->_reader->ReadString();
            entry.m_effectContainerType = this->_reader->ReadString();
            entry.m_dontTriggerAnything = this->_reader->ReadBool();
            entry.m_isPersonal = this->_reader->ReadBool();
            entry.m_isDecursable = this->_reader->ReadBool();
            entry.m_notifyInChatForCaster = this->_reader->ReadBool();
            entry.m_notifyInChatForTarget = this->_reader->ReadBool();
            entry.m_notifyInChatWithCasterName = this->_reader->ReadBool();
            entry.m_scriptFileId = this->_reader->ReadInt();
            entry.m_durationInCasterTurn = this->_reader->ReadBool();
            entry.m_effectProperties = this->_reader->ReadIntArray();
            entry.m_displayInSpellDescription = this->_reader->ReadBool();
            entry.m_displayInStateBar = this->_reader->ReadBool();
            entry.m_recomputeAreaOfEffectDisplay = this->_reader->ReadBool();
            entry.m_isInTurnInFight = this->_reader->ReadBool();
            entry.m_notifyInChat = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for StaticEffectStorage";
    }
};

#endif // BINARYDATA_STATICEFFECTSTORAGE_H
