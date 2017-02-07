#include "Server/WorldSession.h"

void WorldSession::SendClientCalendarSync()
{
    WorldPacket data(SMSG_CLIENT_CALENDAR_SYNC);
    // m_synchronizationTime
    data << (quint64) QDateTime::currentDateTime().toTime_t() * 1000;
    SendPacket(data);
}

void WorldSession::HandleServerTimeCommand(WorldPacket& /*packet*/)
{
    WorldPacket data(SMSG_SERVER_TIME_COMMAND);
    data << (quint64)QDateTime::currentDateTime().toTime_t() * 1000;
    data << quint8(1); // is day (1) or night (0) ?
    data << float(0.0f); // time state, day/night starting [f < 10], day/night ending [f > 90], day/night during [the rest]
    SendPacket(data);
}
