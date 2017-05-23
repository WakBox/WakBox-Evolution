#ifndef BINARYDATA_APTITUDESTORAGE_H
#define BINARYDATA_APTITUDESTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AptitudeStorage : public BinaryDataStorage<T>
{
public:
    AptitudeStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AptitudeBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_breedId = this->_reader->ReadShort();
            entry.m_characteristicId = this->_reader->ReadByte();
            entry.m_uiId = this->_reader->ReadInt();
            entry.m_aptitudeGfxId = this->_reader->ReadInt();
            entry.m_spellGfxId = this->_reader->ReadInt();
            entry.m_maxLevel = this->_reader->ReadShort();
            entry.m_constantCost = this->_reader->ReadInt();
            entry.m_variableCost = this->_reader->ReadIntArray();
            entry.m_linkedSpellId = this->_reader->ReadInt();
            entry.m_levelUnlock = this->_reader->ReadIntArray();
            entry.m_effectIds = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AptitudeStorage";
    }
};

#endif // BINARYDATA_APTITUDESTORAGE_H
