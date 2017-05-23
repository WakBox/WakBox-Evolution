#ifndef BINARYDATA_AREAEFFECTSTORAGE_H
#define BINARYDATA_AREAEFFECTSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AreaEffectStorage : public BinaryDataStorage<T>
{
public:
    AreaEffectStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AreaEffectBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_scriptId = this->_reader->ReadInt();
            entry.m_areaAreaId = this->_reader->ReadInt();
            entry.m_maxExecutionCount = this->_reader->ReadInt();
            entry.m_targetsToShow = this->_reader->ReadInt();
            entry.m_canBeTargeted = this->_reader->ReadBool();
            entry.m_obstacleForAI = this->_reader->ReadBool();
            entry.m_shouldStopMovement = this->_reader->ReadBool();
            entry.m_canBeTargetedByAI = this->_reader->ReadBool();
            entry.m_canBeDestroyed = this->_reader->ReadBool();
            entry.m_type = this->_reader->ReadString();
            entry.m_areaAreaParams = this->_reader->ReadIntArray();
            entry.m_applicationTriggers = this->_reader->ReadIntArray();
            entry.m_unapplicationTriggers = this->_reader->ReadIntArray();
            entry.m_destructionTriggers = this->_reader->ReadIntArray();
            entry.m_deactivationDelay = this->_reader->ReadFloatArray();
            entry.m_params = this->_reader->ReadFloatArray();
            entry.m_properties = this->_reader->ReadIntArray();
            entry.m_effectIds = this->_reader->ReadIntArray();
            entry.m_areaGfx = this->_reader->ReadString();
            entry.m_areaCellGfx = this->_reader->ReadString();
            entry.m_aps = this->_reader->ReadString();
            entry.m_cellAps = this->_reader->ReadString();
            entry.m_maxLevel = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AreaEffectStorage";
    }
};

#endif // BINARYDATA_AREAEFFECTSTORAGE_H
