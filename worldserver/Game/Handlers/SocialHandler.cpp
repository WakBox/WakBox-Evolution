#include "Server/WorldSession.h"

void WorldSession::SendFriendList()
{
    WorldPacket data(SMSG_FRIEND_LIST);
    data << quint8(0);
    SendPacket(data);
}

void WorldSession::SendIgnoreList()
{
    WorldPacket data(SMSG_IGNORE_LIST);
    data << quint8(0);
    SendPacket(data);
}
