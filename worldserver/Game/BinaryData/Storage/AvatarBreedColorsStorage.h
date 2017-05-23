#ifndef BINARYDATA_AVATARBREEDCOLORSSTORAGE_H
#define BINARYDATA_AVATARBREEDCOLORSSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class AvatarBreedColorsStorage : public BinaryDataStorage<T>
{
public:
    AvatarBreedColorsStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            AvatarBreedColorsBinaryData entry;

            entry.m_id = this->_reader->ReadInt();

            qint32 valueCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < valueCount; ++i)
            {
                Data data;

                data.m_sex = this->_reader->ReadByte();
                data.m_defaultSkinIndex = this->_reader->ReadByte();
                data.m_defaultSkinFactor = this->_reader->ReadByte();
                data.m_defaultHairIndex = this->_reader->ReadByte();
                data.m_defaultHairFactor = this->_reader->ReadByte();
                data.m_defaultPupilIndex = this->_reader->ReadByte();

                qint32 skinColorCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < skinColorCount; ++j)
                {
                    Color color;

                    color.m_red = this->_reader->ReadFloat();
                    color.m_green = this->_reader->ReadFloat();
                    color.m_blue = this->_reader->ReadFloat();
                    color.m_alpha = this->_reader->ReadFloat();

                    data.m_skinColors.push_back(color);
                }

                qint32 hairColorCount = this->_reader->ReadInt();

                for (qint32 k = 0; k < hairColorCount; ++k)
                {
                    Color color;

                    color.m_red = this->_reader->ReadFloat();
                    color.m_green = this->_reader->ReadFloat();
                    color.m_blue = this->_reader->ReadFloat();
                    color.m_alpha = this->_reader->ReadFloat();

                    data.m_hairColors.push_back(color);
                }

                qint32 pupilColorCount = this->_reader->ReadInt();

                for (qint32 l = 0; l < pupilColorCount; ++l)
                {
                    Color color;

                    color.m_red = this->_reader->ReadFloat();
                    color.m_green = this->_reader->ReadFloat();
                    color.m_blue = this->_reader->ReadFloat();
                    color.m_alpha = this->_reader->ReadFloat();

                    data.m_pupilColors.push_back(color);
                }

                entry.m_values.push_back(data);
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for AvatarBreedColorsStorage";
    }
};

#endif // BINARYDATA_AVATARBREEDCOLORSSTORAGE_H
