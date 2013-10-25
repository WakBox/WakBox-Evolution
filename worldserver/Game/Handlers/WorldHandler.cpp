#include "Server/WorldSession.h"

void WorldSession::HandleWorldSelect(WorldPacket& packet)
{
    quint32 worldId;
    packet >> worldId;
    qDebug() << worldId;

    WorldPacket data(SMSG_WORLD_SELECT_RESULT);
    data << worldId;
    data << quint8(0); // 0 = success, 1 = error
    SendPacket(data);

    WorldPacket data2(SMSG_SERVER_TIME);
    data2 << (quint64)QDateTime::currentDateTime().toTime_t() * 1000;
    SendPacket(data2);

    WorldPacket data3(SMSG_CHAR_LIST);
    data3 << quint8(1);//Character count
    data3 << quint16(64);//Mark
    data3 << quint8(4);//Block type

    data3 << quint64(1); // CharacterId
    data3 << quint8(0);
    data3 << quint64(1); // AccountId

    data3.WriteString("Monkeysan", true);
    data3 << quint16(12);

    data3 << quint8(0);
    data3 << quint8(0);
    data3 << quint8(0);
    data3 << quint8(0);
    data3 << quint8(2);
    data3 << quint8(0);
    data3 << quint8(4);
    data3 << quint8(0);
    data3 << qint16(-1);

    data3 << quint8(0);//Stuff

    data3 << quint8(1);

    data3 << quint64(0); // XP
    data3 << quint16(0);//Freepoints
    data3 << quint16(0);
    data3 << quint16(0);
    data3 << quint32(0);

    data3 << quint32(1);//Nation
    SendPacket(data3);
}
