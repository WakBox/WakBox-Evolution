#include "Server/WorldSession.h"

void WorldSession::HandleGroupInvite(WorldPacket& packet)
{
    quint8 unk; // 1 = chat, 0 = by ui ?
    quint8 nameOrGuid;
    quint64 guid, unkLong;

    packet >> unk;
    packet >> nameOrGuid; // 0 = name, 1 = guid

    if (nameOrGuid == 0)
        packet.ReadString();
    else
        packet >> guid;

    // Unk, always 0 ?
    packet >> unkLong;

    qDebug() << "Group Invite : " << unk << " | " << nameOrGuid;

    // Reponse avec opcode 504
}
