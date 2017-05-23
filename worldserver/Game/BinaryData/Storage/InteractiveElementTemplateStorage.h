#ifndef BINARYDATA_INTERACTIVEELEMENTTEMPLATESTORAGE_H
#define BINARYDATA_INTERACTIVEELEMENTTEMPLATESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class InteractiveElementTemplateStorage : public BinaryDataStorage<T>
{
public:
    InteractiveElementTemplateStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            InteractiveElementTemplateBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_modelType = this->_reader->ReadShort();
            entry.m_worldId = this->_reader->ReadShort();
            entry.m_x = this->_reader->ReadInt();
            entry.m_y = this->_reader->ReadInt();
            entry.m_z = this->_reader->ReadShort();
            entry.m_initialState = this->_reader->ReadShort();
            entry.m_initiallyVisible = this->_reader->ReadBool();
            entry.m_initiallyUsable = this->_reader->ReadBool();
            entry.m_blockingMovement = this->_reader->ReadBool();
            entry.m_blockingLos = this->_reader->ReadBool();
            entry.m_direction = this->_reader->ReadByte();
            entry.m_activationPattern = this->_reader->ReadShort();
            entry.m_parameter = this->_reader->ReadString();
            entry.m_templateId = this->_reader->ReadInt();
            entry.m_properties = this->_reader->ReadIntArray();

            qint32 positionsTriggerCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < positionsTriggerCount; ++i)
            {
                Point3 point3;

                point3.m_x = this->_reader->ReadInt();
                point3.m_y = this->_reader->ReadInt();
                point3.m_z = this->_reader->ReadShort();

                entry.m_positionsTrigger.push_back(point3);
            }


            qint32 actionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < actionCount; ++i)
            {
                TShortIntHashMap(actionCount); tShortIntHashMap(actionCount);;


                entry.m_actions.push_back(tShortIntHashMap(actionCount););
            }


            qint32 actionKey = this->_reader->ReadShort();

            for (qint32 i = 0; i < actionKey; ++i)
            {
                ReadInt(); readInt();;


                entry.actionValue.push_back(readInt(););
            }

            entry.m_views = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for InteractiveElementTemplateStorage";
    }
};

#endif // BINARYDATA_INTERACTIVEELEMENTTEMPLATESTORAGE_H
