#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

class WorldPacket
{
public:
    WorldPacket(quint16 opcode, QByteArray packet) : m_opcode(opcode), m_stream(packet)
    {
    }

    quint16 GetOpcode() const
    {
        return m_opcode;
    }

    QByteArray GetPacket() const
    {
        return m_buffer;
    }

    template <class T>
    WorldPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
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

    QString ReadString(quint16 length)
    {
        QByteArray bytes;
        bytes.resize(length);

        for (quint16 i = 0; i < length; ++i)
            bytes[i] = Read<qint8>();

        return QString(bytes);
    }

private:
    quint16 m_size;
    qint8 m_unk;
    quint16 m_opcode;

    QByteArray m_buffer;
    QDataStream m_stream;
};

#endif
