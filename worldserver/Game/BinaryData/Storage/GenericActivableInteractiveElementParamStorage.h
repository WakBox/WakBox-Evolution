#ifndef BINARYDATA_GENERICACTIVABLEINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_GENERICACTIVABLEINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class GenericActivableInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    GenericActivableInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            GenericActivableInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 visualCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < visualCount; ++i)
            {
                Visual visual;

                visual.m_id = this->_reader->ReadInt();
                visual.m_visualId = this->_reader->ReadInt();
                visual.m_itemConsumed = this->_reader->ReadInt();
                visual.m_itemQuantity = this->_reader->ReadInt();
                visual.m_doConsumeItem = this->_reader->ReadBool();
                visual.m_kamaCost = this->_reader->ReadInt();
                visual.m_distributionDuration = this->_reader->ReadInt();
                qint32 groupActionCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < groupActionCount; ++j)
                {
                    GroupAction groupAction;

                    groupAction.m_id = this->_reader->ReadInt();
                    groupAction.m_criteria = this->_reader->ReadString();
                    groupAction.m_weight = this->_reader->ReadFloat();
                    qint32 actionCount = this->_reader->ReadInt();

                    for (qint32 k = 0; k < actionCount; ++k)
                    {
                        Action action;

                        action.m_actionId = this->_reader->ReadInt();
                        action.m_actionTypeId = this->_reader->ReadInt();
                        action.m_criteria = this->_reader->ReadString();
                        action.m_actionParams = this->_reader->ReadStringArray();

                        groupAction.m_actions.push_back(action);
                    }

                    visual.m_groupActions.push_back(groupAction);
                }

                entry.m_visuals.push_back(visual);
            }

            entry.if (buffer.get() != 0) { = this->_reader->ReadByte();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for GenericActivableInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_GENERICACTIVABLEINTERACTIVEELEMENTPARAMSTORAGE_H
