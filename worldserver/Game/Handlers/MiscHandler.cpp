#include "Server/WorldSession.h"

void WorldSession::HandleClientLanguage(WorldPacket& packet)
{
    QString clientLanguage = packet.ReadString(2);
    qDebug() << "Client language : " << clientLanguage;

    // Send packet opcode 9 ?
}

void WorldSession::HandlePingCommand(WorldPacket& packet)
{
    quint8 serverGroup;
    quint32 key;
    quint64 clientTime;

    packet >> serverGroup;
    packet >> key;
    packet >> clientTime;

    qDebug() << "[ " << serverGroup <<  " , " << key << " ] Client time : " << clientTime;

    WorldPacket data(SMSG_PING_COMMAND);
    data << serverGroup;
    data << key;
    data << clientTime;

    // unk
    data << quint64(0);
    data << quint64(0);

    SendPacket(data);
}

void WorldSession::HandleWhoisCommand(WorldPacket &packet)
{
    // It's case insensitive !
    QString charName = packet.ReadString();
    qDebug() << "Whois " << charName;

    WorldPacket data(SMSG_WHOIS_COMMAND);
    data << quint8(0); // Whois result
    data.WriteString(charName + "(" + GetAccountInfos().pseudo + ")", STRING_SIZE_2);
    SendPacket(data);
}
