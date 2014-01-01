#include "Server/WorldSession.h"

void WorldSession::SendServerTime()
{
    WorldPacket data(SMSG_SERVER_TIME);
    data << (quint64)QDateTime::currentDateTime().toTime_t() * 1000;
    SendPacket(data);
}
