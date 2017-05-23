#ifndef BINARYDATA_HAVENWORLDBUILDINGSTORAGE_H
#define BINARYDATA_HAVENWORLDBUILDINGSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBuildingStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBuildingStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBuildingBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_catalogEntryId = this->_reader->ReadShort();
            entry.m_kamaCost = this->_reader->ReadInt();
            entry.m_ressourceCost = this->_reader->ReadInt();
            entry.m_workersGranted = this->_reader->ReadByte();
            entry.m_workers = this->_reader->ReadByte();
            entry.m_editorGroupId = this->_reader->ReadInt();
            entry.m_canBeDestroyed = this->_reader->ReadBool();

            qint32 interactiveCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < interactiveCount; ++i)
            {
                Interactive interactive;

                interactive.m_uid = this->_reader->ReadInt();
                interactive.m_templateId = this->_reader->ReadInt();
                interactive.m_x = this->_reader->ReadByte();
                interactive.m_y = this->_reader->ReadByte();
                interactive.m_z = this->_reader->ReadByte();

                entry.m_interactives.push_back(interactive);
            }

            qint32 skinCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < skinCount; ++i)
            {
                Skin skin;

                skin.m_itemId = this->_reader->ReadInt();
                skin.m_editorGroupId = this->_reader->ReadInt();

                entry.m_skins.push_back(skin);
            }

            entry.m_effectIds = this->_reader->ReadIntArray();

            qint32 worldEffectCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < worldEffectCount; ++i)
            {
                WorldEffect worldEffect;

                worldEffect.m_buffId = this->_reader->ReadInt();

                entry.m_worldEffects.push_back(worldEffect);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBuildingStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBUILDINGSTORAGE_H
