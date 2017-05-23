#ifndef BINARYDATA_HAVENWORLDBUILDINGCATALOGSTORAGE_H
#define BINARYDATA_HAVENWORLDBUILDINGCATALOGSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class HavenWorldBuildingCatalogStorage : public BinaryDataStorage<T>
{
public:
    HavenWorldBuildingCatalogStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            HavenWorldBuildingCatalogBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_order = this->_reader->ReadInt();
            entry.m_buildingType = this->_reader->ReadInt();
            entry.m_categoryId = this->_reader->ReadInt();
            entry.m_buyable = this->_reader->ReadBool();
            entry.m_maxQuantity = this->_reader->ReadShort();
            entry.m_isDecoOnly = this->_reader->ReadBool();
            entry.m_buildingSoundId = this->_reader->ReadInt();

            qint32 buildingConditionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < buildingConditionCount; ++i)
            {
                BuildingCondition buildingCondition;

                buildingCondition.m_buildingTypeNeeded = this->_reader->ReadInt();
                buildingCondition.m_quantity = this->_reader->ReadInt();

                entry.m_buildingCondition.push_back(buildingCondition);
            }


            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for HavenWorldBuildingCatalogStorage";
    }
};

#endif // BINARYDATA_HAVENWORLDBUILDINGCATALOGSTORAGE_H
