#ifndef BINARYDATASTORAGE_H
#define BINARYDATASTORAGE_H

#include <QtCore>

#include "BinaryData/BinaryReader.h"
#include "BinaryData/BinaryDataStructure.h"

struct Row
{
    qint64 id;
    qint32 offset;
    qint32 size;
    qint8 seed;
};

typedef QMap<int, Row> Rows;

template<class T>

class BinaryDataStorage
{
public:
    BinaryDataStorage() : _reader(nullptr) { }
    ~BinaryDataStorage() { }

    void InitWith(QByteArray bdata, qint8 fileId)
    {
        BinaryReader reader(bdata, fileId);

        int rowsCount = reader.ReadInt();

        for (int i = 0; i < rowsCount; ++i)
        {
            Row row;
            row.id = reader.ReadLong();
            row.offset = reader.ReadInt();
            row.size = reader.ReadInt();
            row.seed = reader.ReadByte();

            m_rows.insert(i, row);
        }

        qint8 indexCount = reader.ReadByte();
        for (qint8 i = 0; i < indexCount; ++i)
        {
            bool unique = reader.ReadByte();

            QString indexName = reader.ReadString();
            qint32 count = reader.ReadInt();

            for (qint32 k = 0; k < count; ++k)
            {
                reader.ReadLong(); // ID

                if (unique)
                {
                    reader.ReadInt();
                }
                else
                {
                    reader.ReadIntArray();
                }
            }
        }

        QByteArray buffer = reader.ReadAllFromCurrentPos();
        _reader = new BinaryReader(buffer, fileId, reader.GetSize());
    }

    virtual void Load() = 0;

    T const* FindEntry(qint32 id) const
    {
        /*typename QHash<qint32, T const*>::const_iterator it = m_entries.find(id);
        if (it != m_entries.end())
            return (T*) &it.value();*/

        return m_entries.value(id, NULL);
    }

protected:
    Rows m_rows;
    BinaryReader* _reader;

    QHash<qint32, T const*> m_entries;
};

#endif // BINARYDATASTORAGE_H
