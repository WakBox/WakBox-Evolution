#include "Server/WorldSession.h"

// Protobuff from 1.54.0 I guess
void WorldSession::SendFriendList()
{
    WorldPacket data(SMSG_FRIEND_LIST);
    //data << quint8(0);
    SendPacket(data);
}

// Not used anymore?
void WorldSession::SendIgnoreList()
{
    /*WorldPacket data(SMSG_IGNORE_LIST);
    data << quint8(0);
    SendPacket(data);*/
}
