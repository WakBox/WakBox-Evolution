#ifndef BINARYDATA_AVATARBREEDSTORAGE_H
#define BINARYDATA_AVATARBREEDSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AvatarBreedStorage : public BinaryDataStorage<T>
{
public:
    AvatarBreedStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AvatarBreedBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_name = this->_reader->ReadString();
            entry.m_backgroundAps = this->_reader->ReadInt();
            entry.m_baseHp = this->_reader->ReadInt();
            entry.m_baseAp = this->_reader->ReadInt();
            entry.m_baseMp = this->_reader->ReadInt();
            entry.m_baseWp = this->_reader->ReadInt();
            entry.m_baseInit = this->_reader->ReadInt();
            entry.m_baseFerocity = this->_reader->ReadInt();
            entry.m_baseFumble = this->_reader->ReadInt();
            entry.m_baseWisdom = this->_reader->ReadInt();
            entry.m_baseTackle = this->_reader->ReadInt();
            entry.m_baseDodge = this->_reader->ReadInt();
            entry.m_baseProspection = this->_reader->ReadInt();
            entry.m_timerCountBeforeDeath = this->_reader->ReadInt();
            entry.m_preferedArea = this->_reader->ReadInt();
            entry.m_spellElements = this->_reader->ReadByteArray();
            entry.m_characRatios = this->_reader->ReadFloatArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AvatarBreedStorage";
    }
};

#endif // BINARYDATA_AVATARBREEDSTORAGE_H
