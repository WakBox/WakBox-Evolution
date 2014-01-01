#include "Server/WorldSession.h"

void WorldSession::HandleWorldSelect(WorldPacket& packet)
{
    quint32 worldId;
    packet >> worldId;

    WorldPacket data(SMSG_WORLD_SELECT_RESULT);
    data << worldId;
    data << quint8(0); // 0 = success, 1 = error
    SendPacket(data);

    SendServerTime();
    SendCharactersList();
}
