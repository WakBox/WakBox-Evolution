#include "Server/WorldSession.h"

void WorldSession::SendWorldSelectResult(bool result)
{
    WorldPacket data(SMSG_WORLD_SELECT_RESULT);
    data << (quint8) !result;
    qDebug() << "WORLD SELECT result : " << (quint8) !result;
    SendPacket(data);
}

void WorldSession::HandleInteractiveElement(WorldPacket &packet)
{
    quint64 id;
    quint16 type;

    packet >> id;
    packet >> type;

    qDebug() << "Client ask for interactive element " << id << " , type " << type;

    ScriptMgr::Instance()->OnInteractiveElementActive(this->GetCharacter(), id, (InteractiveElementType)type);
}

void WorldSession::SendUpdateObject()
{
    WorldPacket data(SMSG_UPDATE_OBJECT);

    data << quint8(0); // 0 = SpawnInWorld, 1= SpawnInMyFight
    data << quint8(1); // Actor count

    // Actor 1
    {
        data << quint8(0); // Actor type (0 = PlayerCharacter, 1 = NonPlayerCharacter.createNpc, 4 = InteractiveNonPlayerCharacter)
        data << qint64(0); // Actor UID

        data.StartBlock<quint16>();
        {
            // if Actor type == 0 (Player)
            // {

                // CharacterSerializerPart
                // data << quint8(9); // FOR_REMOTE_CHARACTER_INFORMATION

                // ID
                // IDENTITY
                // NAME
                // BREED
                // GUILD_BLAZON
                // GUILD_ID
                // POSITION
                // APPEARANCE
                // PUBLIC_CHARACTERISTICS
                // FIGHT_PROPERTIES
                // FIGHT
                // EQUIPMENT_APPEARANCE
                // RUNNING_EFFECTS
                // CURRENT_MOVEMENT_PATH
                // WORLD_PROPERTIES
                // GROUP
                // TEMPLATE
                // COLLECT
                // PET
                // OCCUPATION
                // XP
                // XP_CHARACTERISTICS
                // CITIZEN_POINT
                // GUILD_REMOTE_INFO
                // NATION_ID
                // NATION_SYNCHRO
                // SOCIAL_STATES
                // ACCOUNT_INFORMATION_REMOTE
                // COMPANION_CONTROLLER_ID
                // VISIBILITY
                // COSMETICS
                // DOWNSCALE_INFO
           // }
        }
        data.EndBlock<quint16>();
    }

    // On first login send packet with all player/creature around the player
    // For the others send packet to all players around the area
    SendPacket(data);
}
