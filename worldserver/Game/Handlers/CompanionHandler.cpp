#include "Server/WorldSession.h"

void WorldSession::SendCompanionList()
{
    WorldPacket data(SMSG_COMPANION_LIST);
    data << (quint8) 0;
    SendPacket(data);
}
