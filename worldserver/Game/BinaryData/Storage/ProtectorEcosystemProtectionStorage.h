#ifndef BINARYDATA_PROTECTORECOSYSTEMPROTECTIONSTORAGE_H
#define BINARYDATA_PROTECTORECOSYSTEMPROTECTIONSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ProtectorEcosystemProtectionStorage : public BinaryDataStorage<T>
{
public:
    ProtectorEcosystemProtectionStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ProtectorEcosystemProtectionBinaryData entry;

            entry.m_protectorId = this->_reader->ReadInt();

            qint32 faunaProtectionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < faunaProtectionCount; ++i)
            {
                ProtectorFaunaProtection protectorFaunaProtection;

                protectorFaunaProtection.m_monsterFamilyId = this->_reader->ReadInt();
                protectorFaunaProtection.m_protectionCost = this->_reader->ReadInt();
                protectorFaunaProtection.m_reintroductionCost = this->_reader->ReadInt();
                protectorFaunaProtection.m_reintroductionItemId = this->_reader->ReadInt();
                protectorFaunaProtection.m_reintroductionItemQty = this->_reader->ReadShort();

                entry.m_faunaProtection.push_back(protectorFaunaProtection);
            }

            qint32 floraProtectionCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < floraProtectionCount; ++i)
            {
                ProtectorFloraProtection protectorFloraProtection;

                protectorFloraProtection.m_resourceFamilyId = this->_reader->ReadInt();
                protectorFloraProtection.m_protectionCost = this->_reader->ReadInt();
                protectorFloraProtection.m_reintroductionCost = this->_reader->ReadInt();
                protectorFloraProtection.m_reintroductionItemId = this->_reader->ReadInt();
                protectorFloraProtection.m_reintroductionItemQty = this->_reader->ReadShort();

                entry.m_floraProtection.push_back(protectorFloraProtection);
            }

            this->m_entries[entry.m_protectorId] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ProtectorEcosystemProtectionStorage";
    }
};

#endif // BINARYDATA_PROTECTORECOSYSTEMPROTECTIONSTORAGE_H
