#ifndef BINARYDATA_HAVENWORLDBUILDINGVISUALDEFINITIONSTORAGE_H
#define BINARYDATA_HAVENWORLDBUILDINGVISUALDEFINITIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBuildingVisualDefinitionStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBuildingVisualDefinitionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBuildingVisualDefinitionBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_buildingId = this->_reader->ReadInt();

            qint32 elementCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < elementCount; ++i)
            {
                VisualElement visualElement;

                visualElement.m_uid = this->_reader->ReadInt();
                visualElement.m_gfxId = this->_reader->ReadInt();
                visualElement.m_hasGuildColor = this->_reader->ReadBool();
                visualElement.m_occluder = this->_reader->ReadBool();
                visualElement.m_height = this->_reader->ReadByte();
                visualElement.m_animName = this->_reader->ReadString();
                visualElement.m_direction = this->_reader->ReadByte();
                visualElement.m_x = this->_reader->ReadByte();
                visualElement.m_y = this->_reader->ReadByte();
                visualElement.m_z = this->_reader->ReadByte();

                entry.m_elements.push_back(visualElement);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBuildingVisualDefinitionStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBUILDINGVISUALDEFINITIONSTORAGE_H
