#ifndef BINARYDATA_GROUNDSTORAGE_H
#define BINARYDATA_GROUNDSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class GroundStorage : public BinaryDataStorage<T>
{
public:
    GroundStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            GroundBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 resourceFertilityCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < resourceFertilityCount; ++i)
            {
                TIntShortHashMap(resourceFertilityCount); tIntShortHashMap(resourceFertilityCount);;


                entry.m_resourceFertility.push_back(tIntShortHashMap(resourceFertilityCount););
            }


            qint32 resourceFertilityKey = this->_reader->ReadInt();

            for (qint32 i = 0; i < resourceFertilityKey; ++i)
            {
                ReadShort(); readShort();;


                entry.resourceFertilityValue.push_back(readShort(););
            }


            qint32 resourceTypeFertilityCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < resourceTypeFertilityCount; ++i)
            {
                TShortShortHashMap(resourceTypeFertilityCount); tShortShortHashMap(resourceTypeFertilityCount);;


                entry.m_resourceTypeFertility.push_back(tShortShortHashMap(resourceTypeFertilityCount););
            }


            qint32 resourceTypeFertilityKey = this->_reader->ReadShort();

            for (qint32 i = 0; i < resourceTypeFertilityKey; ++i)
            {
                ReadShort(); readShort();;


                entry.resourceTypeFertilityValue.push_back(readShort(););
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for GroundStorage";
    }
};

#endif // BINARYDATA_GROUNDSTORAGE_H
