#ifndef BINARYDATA_SKILLACTIONSTORAGE_H
#define BINARYDATA_SKILLACTIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class SkillActionStorage : public BinaryDataStorage<T>
{
public:
    SkillActionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            SkillActionBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_mruGfxId = this->_reader->ReadInt();
            entry.m_mruKey = this->_reader->ReadString();
            entry.m_associatedItems = this->_reader->ReadIntArray();
            entry.m_animLinkage = this->_reader->ReadString();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for SkillActionStorage";
    }
};

#endif // BINARYDATA_SKILLACTIONSTORAGE_H
