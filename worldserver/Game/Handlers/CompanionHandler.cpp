#include "Server/WorldSession.h"

void WorldSession::SendCompanionList()
{
    WorldPacket data(SMSG_COMPANION_LIST);
    data << (quint8) 0;
    SendPacket(data);

    /*
    var size = packet.ReadByte("companionListSize");
    for (var i = 0; i < size; ++i)
    {
        packet.ReadLong("companion_id");
        packet.ReadShort("breedId");
        packet.ReadLong("ownerId");
        packet.ReadLong("xp");

        var strSize = packet.ReadInt("size");
        packet.ReadString(strSize, "name");

        packet.ReadByte("isUnlocked");
        packet.ReadInt("currentHp");
        packet.ReadInt("maxHp");

        packet.ReadInt("serializationVersion");

        packet.ReadShort("Size of ?");
        // TODO!
    }
    */
}
