#ifndef BINARYDATA_EXCHANGEINTERACTIVEELEMENTPARAMSTORAGE_H
#define BINARYDATA_EXCHANGEINTERACTIVEELEMENTPARAMSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class ExchangeInteractiveElementParamStorage : public BinaryDataStorage<T>
{
public:
    ExchangeInteractiveElementParamStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            ExchangeInteractiveElementParamBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_apsId = this->_reader->ReadInt();
            entry.m_visualMruId = this->_reader->ReadInt();
            entry.m_sortTypeId = this->_reader->ReadByte();

            qint32 exchangeCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < exchangeCount; ++i)
            {
                Exchange exchange;

                exchange.m_exchangeId = this->_reader->ReadInt();
                exchange.m_criteria = this->_reader->ReadString();
                qint32 consumableCount = this->_reader->ReadInt();

                for (qint32 j = 0; j < consumableCount; ++j)
                {
                    Consumable consumable;

                    consumable.m_itemId = this->_reader->ReadInt();
                    consumable.m_quantity = this->_reader->ReadShort();

                    exchange.m_consumables.push_back(consumable);
                }

                exchange.m_consumableKama = this->_reader->ReadInt();
                exchange.m_consumablePvpMoney = this->_reader->ReadInt();

                qint32 resultingCount = this->_reader->ReadInt();

                for (qint32 k = 0; k < resultingCount; ++k)
                {
                    Resulting resulting;

                    resulting.m_itemId = this->_reader->ReadInt();
                    resulting.m_quantity = this->_reader->ReadShort();
                    resulting.m_forcedBindType = this->_reader->ReadByte();

                    exchange.m_resultings.push_back(resulting);
                }

                exchange.m_resultingKama = this->_reader->ReadInt();

                entry.m_exchanges.push_back(exchange);
            }

            qint8 hasChaosParam = this->_reader->ReadByte();
            if (hasChaosParam)
            {
                entry.m_chaosParams.m_chaosLevel = this->_reader->ReadInt();
                entry.m_chaosParams.m_chaosCollectorParamId = this->_reader->ReadInt();
            }

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for ExchangeInteractiveElementParamStorage";
    }
};

#endif // BINARYDATA_EXCHANGEINTERACTIVEELEMENTPARAMSTORAGE_H
