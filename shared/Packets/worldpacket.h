#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

struct Block
{
    qint64 pos;
    qint64 dataWritten;
};

typedef QMap<quint8, Block> BlockMap;

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
        AddDataSizeToBlock((qint64)sizeof(T));

        return *this;
    }

    void WriteBytes(const char* s, uint len)
    {
        m_stream.writeBytes(s, len);
        AddDataSizeToBlock((qint64)len);
    }

    void WriteRawBytes(const char* s, int len)
    {
        m_stream.writeRawData(s, len);
        AddDataSizeToBlock((qint64)len);
    }

    void WriteString(QString s)
    {
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

    template <typename T>
    void StartBlock(quint8 index = 0)
    {
        Block block;
        block.pos = m_stream.device()->pos();
        block.dataWritten = 0;

        m_blocks.insert(index, block);

        T v;
        *this << T(0);
    }

    void AddDataSizeToBlock(qint64 len)
    {
        if (m_blocks.size() > 0)
            m_blocks[m_blocks.size() - 1].dataWritten += len;
    }

    template <class T>
    void EndBlock(quint8 index = 0)
    {
        Block block = m_blocks.take(index);
        m_stream.device()->seek(block.pos);

        *this << T(block.dataWritten);
    }

private:
    quint16 m_opcode;

    QByteArray m_buffer;
    QDataStream m_stream;

    BlockMap m_blocks;
};

#endif
