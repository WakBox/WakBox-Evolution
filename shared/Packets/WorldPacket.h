#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>

#include "Packet.h"

class WorldPacket : public Packet
{
public:
    WorldPacket(quint16 opcode, QByteArray packet = QByteArray()) : Packet(opcode, packet)
    {
        if (packet.isEmpty())
        {
            *this << (quint16)0;
            *this << m_opcode;
        }
    }

    void WriteHeader()
    {
        m_stream.device()->reset();
        *this << (quint16)m_stream.device()->size();
    }
};

#endif
