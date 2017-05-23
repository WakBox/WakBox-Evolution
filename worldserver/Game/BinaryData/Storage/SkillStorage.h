#ifndef BINARYDATA_SKILLSTORAGE_H
#define BINARYDATA_SKILLSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class SkillStorage : public BinaryDataStorage<T>
{
public:
    SkillStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            SkillBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_type = this->_reader->ReadInt();
            entry.m_scriptId = this->_reader->ReadInt();
            entry.m_mruGfxId = this->_reader->ReadInt();
            entry.m_mruKey = this->_reader->ReadString();
            entry.m_animLinkage = this->_reader->ReadString();
            entry.m_associatedItemTypes = this->_reader->ReadIntArray();
            entry.m_associatedItems = this->_reader->ReadIntArray();
            entry.m_maxLevel = this->_reader->ReadInt();
            entry.m_isInnate = this->_reader->ReadBool();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for SkillStorage";
    }
};

#endif // BINARYDATA_SKILLSTORAGE_H
