#ifndef BINARYDATASTORAGE_H
#define BINARYDATASTORAGE_H

#include <QtCore>

#include "BinaryData/BinaryDataStructure.h"

struct Row
{
    qint64 id;
    qint32 offset;
    qint32 size;
    qint8 seed;
};

typedef QMap<int, Row> Rows;

class BinaryDataStorage
{
public:
    BinaryDataStorage() : m_stream(&m_buffer, QIODevice::ReadOnly), m_size(0) {  }
    ~BinaryDataStorage() { Clear();  }

    void Init(QByteArray bdata, qint8 fileId)
    {
        m_buffer = QByteArray(bdata);
        m_fileId = fileId;

        m_stream.setByteOrder(QDataStream::LittleEndian);
        m_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

        *this >> m_size;
        m_size += 756423;

        m_seed = qint8(m_fileId ^ m_size);

        ReadFile();
    }

    void SetBufferPosition(qint64 pos)
    {
        m_stream.device()->seek(pos);
    }

    void Seed()
    {
        m_seed += (qint8)(m_fileId * (m_stream.device()->pos()) + m_size);
    }

    void ReadFile()
    {
        int rowsCount = ReadInt();
        qDebug() << "rowsCount:" << rowsCount;

        for (int i = 0; i < rowsCount; ++i)
        {
            Row row;
            row.id = ReadLong();
            row.offset = ReadInt();
            row.size = ReadInt();
            row.seed = ReadByte();

            m_rows.insert(i, row);
        }

        qint8 indexCount = ReadByte();
        qDebug() << "Blocks : " << indexCount;
        for (qint8 i = 0; i < indexCount; ++i)
        {
            bool unique = ReadByte();

            QString indexName = ReadString();
            qint32 count = ReadInt();

            for (qint32 k = 0; k < count; ++k)
            {
                ReadLong(); // ID

                if (unique)
                {
                    ReadInt();
                }
                else
                {
                    ReadIntArray();
                }
            }
        }

        m_buffer = m_stream.device()->readAll();
        m_stream.device()->seek(0);

        Seed();
    }

    virtual void Load() = 0;

    void Clear()
    {

    }

    template <class T>
    BinaryDataStorage& operator>>(T& value)
    {
        m_stream >> value;
        return *this;
    }

    template <typename T>
    T Read()
    {
        Seed();

        T v;
        *this >> v;
        v = v - m_seed;

        return v;
    }

    float ReadFloat()
    {
        Seed();

        float v;
        *this >> v;

        return v;
    }

    bool ReadBool() { return Read<bool>(); }
    qint32 ReadInt() { return Read<qint32>(); }
    quint32 ReadUInt() { return Read<quint32>(); }
    //double ReadDouble() { return Read<double>(); }
    qint16 ReadShort() { return Read<qint16>(); }
    quint16 ReadUShort() { return Read<quint16>(); }
    qint8 ReadByte(){ return Read<qint8>(); }
    quint8 ReadUByte() { return Read<quint8>(); }
    qint64 ReadLong() { return Read<qint64>(); }
    quint64 ReadULong() { return Read<quint64>(); }

    void ReadBytes(char*& s, uint len)
    {
        m_stream.readBytes(s, len);
    }

    void ReadRawBytes(char* s, int len)
    {
        m_stream.readRawData(s, len);
    }

    QString ReadString()
    {
        qint32 len = ReadInt();

        QByteArray bytes;
        bytes.resize(len);

        for (qint32 i = 0; i < len; ++i)
        {
            qint8 v;
            *this >> v;
            bytes[i] = v;
        }

        QString str = QString::fromUtf8(bytes);

        return str;
    }

    QStringList ReadStringArray()
    {
        QStringList stringArray, v;
        qint32 size = ReadInt();

        for (qint32 i = 0; i < size; ++i)
        {
            QString value = ReadString();
            stringArray.push_back(value);
            v.push_back(value);
        }

        return stringArray;
    }

    QList<qint32> ReadIntArray()
    {
        QList<qint32> intArray;
        qint32 size = ReadInt();
        QStringList v;

        for (qint32 i = 0; i < size; ++i)
        {
            qint32 value = ReadInt();
            intArray.push_back(value);
            v.push_back(QString::number(value));
        }

        return intArray;
    }

    QList<float> ReadFloatArray()
    {
        QList<float> floatArray;
        qint32 size = ReadInt();
        QStringList v;

        for (qint32 i = 0; i < size; ++i)
        {
            float value = ReadFloat();
            floatArray.push_back(value);
            v.push_back(QString::number(value));
        }

        return floatArray;
    }

    QList<qint8> ReadByteArray()
    {
        QList<qint8> byteArray;
        qint32 size = ReadInt();
        QStringList v;

        for (qint32 i = 0; i < size; ++i)
        {
            qint8 value = ReadByte();
            byteArray.push_back(value);
            v.push_back(QString::number(value));
        }

        return byteArray;
    }

    QList<qint16> ReadShortArray()
    {
        QList<qint16> shortArray;
        qint32 size = ReadInt();
        QStringList v;

        for (qint32 i = 0; i < size; ++i)
        {
            qint16 value = ReadShort();
            shortArray.push_back(value);
            v.push_back(QString::number(value));
        }

        return shortArray;
    }

    QList<qint64> ReadLongArray()
    {
        QList<qint64> longArray;
        qint32 size = ReadInt();
        QStringList v;

        for (qint32 i = 0; i < size; ++i)
        {
            qint64 value = ReadLong();
            longArray.push_back(value);
            v.push_back(QString::number(value));
        }

        return longArray;
    }

private:
    QByteArray m_buffer;
    QDataStream m_stream;

    qint8 m_fileId;
    qint32 m_size;
    qint8 m_seed;

protected:
    Rows m_rows;
};

#endif // BINARYDATASTORAGE_H
