#ifndef BINARYDATA_STATESTORAGE_H
#define BINARYDATA_STATESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class StateStorage : public BinaryDataStorage<T>
{
public:
    StateStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            StateBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_maxLevel = this->_reader->ReadShort();
            entry.m_endTrigger = this->_reader->ReadIntArray();
            entry.m_duration = this->_reader->ReadIntArray();
            entry.m_durationInc = this->_reader->ReadFloatArray();
            entry.m_endsAtEndOfTurn = this->_reader->ReadBool();
            entry.m_isDurationInFullTurns = this->_reader->ReadBool();
            entry.m_inTurnInFight = this->_reader->ReadBool();
            entry.m_isReplacable = this->_reader->ReadBool();
            entry.m_isTransmigrable = this->_reader->ReadBool();
            entry.m_hmiActions = this->_reader->ReadString();
            entry.m_applyCriterion = this->_reader->ReadString();
            entry.m_isCumulable = this->_reader->ReadBool();
            entry.m_durationInCasterTurn = this->_reader->ReadBool();
            entry.m_durationInRealTime = this->_reader->ReadBool();
            entry.m_effectIds = this->_reader->ReadIntArray();
            entry.m_stateImmunities = this->_reader->ReadIntArray();
            entry.m_stateShouldBeSaved = this->_reader->ReadBool();
            entry.m_decursable = this->_reader->ReadBool();
            entry.m_stateType = this->_reader->ReadByte();
            entry.m_statePowerType = this->_reader->ReadByte();
            entry.m_isReapplyEvenAtMaxLevel = this->_reader->ReadBool();
            entry.m_timelineVisible = this->_reader->ReadBool();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_displayCasterName = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for StateStorage";
    }
};

#endif // BINARYDATA_STATESTORAGE_H
