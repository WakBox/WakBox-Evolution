#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

typedef QMap<quint8, qint64> BlockPosMap;

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

    void WriteString(QString s, bool bigString = false)
    {
        if (bigString)
            *this << (quint16)s.length();
        else
            *this << (quint8)s.length();

        WriteRawBytes(s.toLatin1().constData(), (uint)s.length());
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

    void ReadRawBytes(char* s, int len)
    {
        m_stream.readRawData(s, len);
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
    void StartBlock(quint8 index = 0)
    {
        m_blockPos.insert(index, m_stream.device()->pos());
        *this << T(0);
    }

    template <class T>
    void EndBlock(quint8 index = 0, qint8 add = 0)
    {
        if (m_blockPos.count() == 0)
            return;

        qint64 pos = m_blockPos.take(index);
        m_stream.device()->seek(pos);

        *this << T(m_stream.device()->size() - pos - sizeof(T) + add);
        m_stream.device()->seek(m_stream.device()->size());
    }

    template <class T>
    void EndBlockAbsolute(quint8 index = 0, qint8 add = 0)
    {
        if (m_blockPos.count() == 0)
            return;

        qint64 pos = m_blockPos.take(index);
        m_stream.device()->seek(pos);

        *this << T(m_stream.device()->size() + add);
        m_stream.device()->seek(m_stream.device()->size());
    }

private:
    quint16 m_opcode;

    QByteArray m_buffer;
    QDataStream m_stream;

    BlockPosMap m_blockPos;
};

#endif
