#include "Server/WorldSession.h"
#include "Utils/Util.h"

void WorldSession::SendCompanionList()
{
    WorldPacket data(SMSG_COMPANION_LIST);

    data << (quint8) 1;
    data << quint64(1562225);
    data << quint16(3075);
    data << quint64(GetAccountInfos().id);
    data << quint64(0);
    data << quint32(0);
    data << quint8(0);
    data << quint32(0);
    data << quint32(0);
    data << quint32(10050002);
    data << quint16(0);

    SendPacket(data);
}
