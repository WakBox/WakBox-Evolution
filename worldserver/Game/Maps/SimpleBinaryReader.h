#ifndef SIMPLEBINARYREADER_H
#define SIMPLEBINARYREADER_H

#include <QtCore>

class SimpleBinaryReader
{
public:
    SimpleBinaryReader(QByteArray file) : m_buffer(file), m_stream(&m_buffer, QIODevice::ReadOnly)
    {
        m_stream.setByteOrder(QDataStream::LittleEndian);
    }

    int remaning() { return m_stream.device()->bytesAvailable(); }

    template <class T>
    SimpleBinaryReader& operator>>(T& value)
    {
        m_stream >> value;
        return *this;
    }

    template <typename T>
    T read()
    {
        T v;
        *this >> v;

        return v;
    }

    qint8 readByte() { return read<qint8>(); }
    qint16 readShort() { return read<qint16>(); }
    qint32 readInt(){ return read<qint32>(); }
    qint64 readLong() { return read<qint64>(); }

private:
    QByteArray m_buffer;
    QDataStream m_stream;
};

#endif // SIMPLEBINARYREADER_H
