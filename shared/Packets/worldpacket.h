#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

class WorldPacket
{
public:
    WorldPacket(quint16 opcode, QByteArray packet = QByteArray()) : m_opcode(opcode), m_buffer(packet), m_stream(&m_buffer, QIODevice::ReadWrite)
    {
        if (packet.isEmpty())
        {
            *this << (quint16)0;
            *this << m_opcode;
        }
    }

    quint16 GetOpcode()
    {
        return m_opcode;
    }

    QByteArray GetPacket()
    {
        return m_buffer;
    }

    void WriteHeader()
    {
        m_stream.device()->reset();
        *this << (quint16)m_stream.device()->size();
    }

    template <class T>
    WorldPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }

    void WriteBytes(const char* s, uint len)
    {
        m_stream.writeBytes(s, len);
    }

    void WriteRawBytes(const char* s, int len)
    {
        m_stream.writeRawData(s, len);
    }

    template <class T>
    WorldPacket& operator>>(T& value)
    {
        m_stream >> value;
        return *this;
    }

    template <typename T>
    T Read()
    {
        T v;
        *this >> v;
        return v;
    }

    void ReadBytes(char*& s, uint len)
    {
        m_stream.readBytes(s, len);
    }

    void ReadRawBytes(char*& s, int len)
    {
        m_stream.readRawData(s, len);
    }

    QString ReadString()
    {
        quint8 len;
        QByteArray bytes;

        *this >> len;
        bytes.resize(len);

        for (quint16 i = 0; i < len; ++i)
            bytes[i] = Read<qint8>();

        return QString(bytes);
    }

private:
    quint16 m_opcode;

    QByteArray m_buffer;
    QDataStream m_stream;
};

#endif
