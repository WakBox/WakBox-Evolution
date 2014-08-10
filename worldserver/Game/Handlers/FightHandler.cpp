#include "Server/WorldSession.h"

void WorldSession::HandleStartFight(WorldPacket& packet)
{
    qint64 targetGuid, unkId;
    packet >> targetGuid;
    packet >> unkId;

    qDebug() << "TargetGUID : " << targetGuid << " | unkId : " << unkId;
}
