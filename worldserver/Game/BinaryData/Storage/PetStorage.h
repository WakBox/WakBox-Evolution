#ifndef BINARYDATA_PETSTORAGE_H
#define BINARYDATA_PETSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class PetStorage : public BinaryDataStorage<T>
{
public:
    PetStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            PetBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_itemRefId = this->_reader->ReadInt();
            entry.m_gfxId = this->_reader->ReadInt();
            entry.m_itemColorRefId = this->_reader->ReadInt();
            entry.m_itemReskinRefId = this->_reader->ReadInt();
            entry.m_health = this->_reader->ReadInt();
            entry.m_minMealInterval = this->_reader->ReadLong();
            entry.m_maxMealInterval = this->_reader->ReadLong();
            entry.m_xpByMeal = this->_reader->ReadByte();
            entry.m_xpPerLevel = this->_reader->ReadShort();
            entry.m_levelMax = this->_reader->ReadShort();
            entry.m_mountType = this->_reader->ReadByte();

            qint32 healthPenaltieCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < healthPenaltieCount; ++i)
            {
                HealthPenalty healthPenalty;

                healthPenalty.m_penaltyType = this->_reader->ReadByte();
                healthPenalty.m_value = this->_reader->ReadByte();

                entry.m_healthPenalties.push_back(healthPenalty);
            }


            qint32 healthItemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < healthItemCount; ++i)
            {
                HealthItem healthItem;

                healthItem.m_itemId = this->_reader->ReadInt();
                healthItem.m_value = this->_reader->ReadInt();

                entry.m_healthItems.push_back(healthItem);
            }


            qint32 mealItemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < mealItemCount; ++i)
            {
                MealItem mealItem;

                mealItem.m_itemId = this->_reader->ReadInt();
                mealItem.m_visible = this->_reader->ReadBool();

                entry.m_mealItems.push_back(mealItem);
            }


            qint32 sleepItemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < sleepItemCount; ++i)
            {
                SleepItem sleepItem;

                sleepItem.m_itemId = this->_reader->ReadInt();
                sleepItem.m_duration = this->_reader->ReadLong();

                entry.m_sleepItems.push_back(sleepItem);
            }

            entry.m_equipmentItems = this->_reader->ReadIntArray();

            qint32 colorItemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < colorItemCount; ++i)
            {
                ColorItem colorItem;

                colorItem.m_itemId = this->_reader->ReadInt();
                colorItem.m_partId = this->_reader->ReadInt();
                colorItem.m_colorABGR = this->_reader->ReadInt();

                entry.m_colorItems.push_back(colorItem);
            }


            qint32 reskinItemCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < reskinItemCount; ++i)
            {
                ReskinItem reskinItem;

                reskinItem.m_itemId = this->_reader->ReadInt();
                reskinItem.m_gfxId = this->_reader->ReadInt();

                entry.m_reskinItems.push_back(reskinItem);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for PetStorage";
    }
};

#endif // BINARYDATA_PETSTORAGE_H
