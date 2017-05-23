#ifndef BINARYDATA_CHARACGAINPERLEVELSTORAGE_H
#define BINARYDATA_CHARACGAINPERLEVELSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class CharacGainPerLevelStorage : public BinaryDataStorage<T>
{
public:
    CharacGainPerLevelStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            CharacGainPerLevelBinaryData entry;

            entry.m_breedId = this->_reader->ReadShort();

            qint32 gainCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < gainCount; ++i)
            {
                TByteFloatHashMap(gainCount); tByteFloatHashMap(gainCount);;


                entry.m_gains.push_back(tByteFloatHashMap(gainCount););
            }


            qint32 gainKey = this->_reader->ReadByte();

            for (qint32 i = 0; i < gainKey; ++i)
            {
                ReadFloat(); readFloat();;


                entry.gainValue.push_back(readFloat(););
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for CharacGainPerLevelStorage";
    }
};

#endif // BINARYDATA_CHARACGAINPERLEVELSTORAGE_H
