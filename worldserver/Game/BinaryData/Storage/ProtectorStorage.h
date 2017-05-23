#ifndef BINARYDATA_PROTECTORSTORAGE_H
#define BINARYDATA_PROTECTORSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ProtectorStorage : public BinaryDataStorage<T>
{
public:
    ProtectorStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ProtectorBinaryData entry;

            entry.m_protectorId = this->_reader->ReadInt();
            entry.m_monsterId = this->_reader->ReadInt();
            entry.m_buffListId = this->_reader->ReadInt();
            entry.m_buffListIdToBuy = this->_reader->ReadInt();
            entry.m_scenarioLootListId = this->_reader->ReadInt();
            entry.m_scenarioLootListIdToBuy = this->_reader->ReadInt();
            entry.m_scenarioLootListIdChaos = this->_reader->ReadInt();
            entry.m_scenarioLootListIdEcosystem = this->_reader->ReadInt();
            entry.m_climateListIdToBuy = this->_reader->ReadInt();
            entry.m_nationId = this->_reader->ReadInt();
            entry.m_territory = this->_reader->ReadInt();
            entry.m_fightStake = this->_reader->ReadInt();
            entry.m_positionX = this->_reader->ReadInt();
            entry.m_positionY = this->_reader->ReadInt();
            entry.m_positionZ = this->_reader->ReadShort();
            entry.m_craftLearnt = this->_reader->ReadIntArray();

            qint32 secretCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < secretCount; ++i)
            {
                ProtectorSecret protectorSecret;

                protectorSecret.m_id = this->_reader->ReadInt();
                protectorSecret.m_achievementGoalId = this->_reader->ReadInt();
                protectorSecret.m_secretGfxId = this->_reader->ReadInt();
                protectorSecret.m_discoveredGfxId = this->_reader->ReadInt();

                entry.m_secrets.push_back(protectorSecret);
            }

            qint32 faunaWillCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < faunaWillCount; ++i)
            {
                ProtectorFaunaWill protectorFaunaWill;

                protectorFaunaWill.m_typeId = this->_reader->ReadInt();
                protectorFaunaWill.m_min = this->_reader->ReadShort();
                protectorFaunaWill.m_max = this->_reader->ReadShort();

                entry.m_faunaWill.push_back(protectorFaunaWill);
            }

            qint32 floraWillCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < floraWillCount; ++i)
            {
                ProtectorFloraWill protectorFloraWill;

                protectorFloraWill.m_typeId = this->_reader->ReadInt();
                protectorFloraWill.m_min = this->_reader->ReadShort();
                protectorFloraWill.m_max = this->_reader->ReadShort();

                entry.m_floraWill.push_back(protectorFloraWill);
            }

            this->m_entries[entry.m_protectorId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ProtectorStorage";
    }
};

#endif // BINARYDATA_PROTECTORSTORAGE_H
