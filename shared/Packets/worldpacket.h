#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>
#include "Opcodes/Opcodes.h"

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

    template<class T>
    WorldPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }

private:
    quint16 m_size;
    qint8 m_unk;
    quint16 m_opcode;

    QByteArray m_buffer;
    QDataStream m_stream;
};

#endif
