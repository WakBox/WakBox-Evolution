#ifndef PACKET_H
#define PACKET_H

#include <QtCore>
#include <QTextStream>

#include "Define.h"

typedef QMap<quint8, qint64> BlockPosMap;

class Packet
{
public:
    Packet(quint16 opcode = 0, QByteArray packet = QByteArray()) : m_opcode(opcode), m_buffer(packet), m_stream(&m_buffer, QIODevice::ReadWrite), m_blockIndex(0)
    {
    }

    quint16 GetOpcode()
    {
        return m_opcode;
    }

    QByteArray GetPacket()
    {
        return m_buffer;
    }

    void Append(Packet& packet)
    {
        WriteRawBytes(packet.GetPacket());
    }

    template <class T>
    Packet& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }

    void WriteBytes(const char* s, uint len)
    {
        m_stream.writeBytes(s, len);
    }

    void WriteRawBytes(QByteArray bytes)
    {
        m_stream.writeRawData(bytes.data(), bytes.length());
    }

    void WriteString(QString s, quint8 size = STRING_SIZE_1)
    {
        if (size == STRING_SIZE_4)
            *this << (quint32)s.length();
        else if (size == STRING_SIZE_2)
            *this << (quint16)s.length();
        else
            *this << (quint8)s.length();

        WriteRawBytes(s.toLatin1());
    }

    template <class T>
    Packet& operator>>(T& value)
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

    void ReadRawBytes(char* s, int len)
    {
        m_stream.readRawData(s, len);
    }

    QString ReadBigString(quint8 size = STRING_SIZE_2)
    {
        quint8 strLen;

        if (size == STRING_SIZE_4)
        {
            quint32 len;
            *this >> len;

            strLen = (quint8)len;
        }
        else
        {
            quint16 len;
            *this >> len;

            strLen = (quint8)len;
        }

        return ReadString(strLen);
    }

    QString ReadString(quint8 len = 0)
    {
        QByteArray bytes;

        if (!len)
            *this >> len;

        bytes.resize(len);

        for (quint16 i = 0; i < len; ++i)
            bytes[i] = Read<qint8>();

        return QString(bytes);
    }

    template <typename T>
    void StartBlock()
    {
        m_blockPos.insert(m_blockIndex++, m_stream.device()->pos());
        *this << T(0);
    }

    template <class T>
    void EndBlock(/*qint8 add = 0*/)
    {
        if (m_blockPos.count() == 0)
            return;

        qint64 pos = m_blockPos.take(--m_blockIndex);
        m_stream.device()->seek(pos);

        *this << T(m_stream.device()->size() - pos - sizeof(T)/* + add*/);
        m_stream.device()->seek(m_stream.device()->size());
    }

    // Not used ??
    /*template <class T>
    void EndBlockAbsolute(quint8 index = 0, qint8 add = 0)
    {
        if (m_blockPos.count() == 0)
            return;

        qint64 pos = m_blockPos.take(index);
        m_stream.device()->seek(pos);

        *this << T(m_stream.device()->size() + add);
        m_stream.device()->seek(m_stream.device()->size());
    }*/

protected:
    quint16 m_opcode;
    QByteArray m_buffer;
    QDataStream m_stream;
    quint8 m_blockIndex;

private:
    BlockPosMap m_blockPos;
};

#endif
