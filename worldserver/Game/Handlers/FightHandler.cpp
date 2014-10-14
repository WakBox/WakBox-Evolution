#include "Server/WorldSession.h"

void WorldSession::HandleStartFight(WorldPacket& packet)
{
    qint64 targetGuid, actionId;
    packet >> targetGuid;
    packet >> actionId;

    qDebug() << "TargetGUID : " << targetGuid << " | actionId : " << actionId;

    WorldPacket data2(SMSG_CHAR_DIRECTION);
    data2 << GetCharacter()->GetGuid();
    data2 << GetCharacter()->GetDirection();
    SendPacket(data2);

    WorldPacket data3(SMSG_UPDATE_CREATURE_STATE);
    data3 << targetGuid;
    data3 << qint8(18);
    SendPacket(data3);

    WorldPacket data(SMSG_START_FIGHT);
    data << targetGuid;
    data << GetCharacter()->GetGuid();
    data << actionId;
    SendPacket(data);

    WorldPacket data4(SMSG_UPDATE_CREATURE_STATE);
    data4 << targetGuid;
    data4 << qint8(-18);
    SendPacket(data3);

    WorldPacket data5(SMSG_SCENARIO_SCRIPT);
    data5 << quint8(0); // Event
    data5 << quint32(12646); // Function
    data5 << quint32(1611); // ScenarioId
    data5 << quint8(0); // Long size?
    SendPacket(data5);

    QList<quint8> ids;
    ids << 75 << 56 << 59 << 84 << 15 << 68 << 71 << 55 << 80 << 58 << 67 << 70 << 73 << 76 << 54 << 79 << 63 << 16 << 66 << 69 << 72;

    WorldPacket data6(SMSG_PROPERTIES_UPDATE);
    data6 << GetCharacter()->GetGuid();
    data6.StartBlock<quint16>();
    {
        data6 << quint8(21); // CharacterPartId
        data6 << quint8(1); // hasProperties

        data6 << quint16(ids.size());
        for (quint8 i = 0; i < ids.size(); ++i)
        {
            data6 << quint8(ids.at(i)); // id
            data6 << quint8(1); // count
        }
    }
    data6.EndBlock<quint16>();
    SendPacket(data6);
}
