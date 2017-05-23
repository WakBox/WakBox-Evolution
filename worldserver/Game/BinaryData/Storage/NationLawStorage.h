#ifndef BINARYDATA_NATIONLAWSTORAGE_H
#define BINARYDATA_NATIONLAWSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class NationLawStorage : public BinaryDataStorage<T>
{
public:
    NationLawStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            NationLawBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_lawConstantId = this->_reader->ReadInt();
            entry.m_params = this->_reader->ReadStringArray();
            entry.m_basePointsModification = this->_reader->ReadInt();
            entry.m_percentPointsModification = this->_reader->ReadInt();
            entry.m_lawPointCost = this->_reader->ReadInt();
            entry.m_lawLocked = this->_reader->ReadBool();
            entry.m_applicableToCitizen = this->_reader->ReadBool();
            entry.m_applicableToAlliedForeigner = this->_reader->ReadBool();
            entry.m_applicableToNeutralForeigner = this->_reader->ReadBool();
            entry.m_restrictedNations = this->_reader->ReadIntArray();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for NationLawStorage";
    }
};

#endif // BINARYDATA_NATIONLAWSTORAGE_H
