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

void WorldSession::SendActorSpawn(WorldSession* actor)
{
    QList<Character*> actorList;

    if (actor)
        actorList.push_back(actor->GetCharacter());
    else
    {
        SessionList const& sessions = sWorld->GetAllSessions();
        for (SessionList::ConstIterator itr = sessions.begin(); itr != sessions.end(); ++itr)
            if ((*itr) && (*itr) != this)
                if (Character* character = (*itr)->GetCharacter())
                    if (character->IsInWorld())
                        actorList.push_back(character);
    }

    qDebug() << "Actor list: " << actorList.count();

    for (QList<Character*>::ConstIterator itr = actorList.begin(); itr != actorList.end(); ++itr)
        qDebug() << ">> " << (*itr)->GetName();

    WorldPacket data(SMSG_ACTOR_SPAWN);

    data << quint8(0); // 0 = SpawnInWorld, 1= SpawnInMyFight
    data << quint8(actorList.count()); // Actor count

    for (QList<Character*>::ConstIterator itr = actorList.begin(); itr != actorList.end(); ++itr)
    {
        data << quint8(0); // Actor type (0 = PlayerCharacter, 1 = NonPlayerCharacter.createNpc, 4 = InteractiveNonPlayerCharacter)
        data << quint64((*itr)->GetGuid());

        data.StartBlock<quint16>();
        {
            // CharacterSerializerPart
            data << quint8(9); // FOR_REMOTE_CHARACTER_INFORMATION

            // ID
            (*itr)->SerializeGuid(data);

            // IDENTITY
            (*itr)->SerializeIdentity(data);

            // NAME
            (*itr)->SerializeName(data);

            // BREED
            (*itr)->SerializeBreed(data);

            // GUILD_BLAZON
            (*itr)->SerializeGuildBlazon(data);

            // GUILD_ID
            (*itr)->SerializeGuildId(data);

            // POSITION
            (*itr)->SerializePosition(data);

            // APPEARANCE
            (*itr)->SerializeAppearance(data);

            // PUBLIC_CHARACTERISTICS
            (*itr)->SerializePublicCharacteristics(data);

            // FIGHT_PROPERTIES
            (*itr)->SerializeFightProperties(data);

            // FIGHT
            (*itr)->SerializeFight(data);

            // EQUIPMENT_APPEARANCE
            (*itr)->SerializeEquipmentAppearance(data);

            // RUNNING_EFFECTS
            (*itr)->SerializeRunningEffects(data);

            // CURRENT_MOVEMENT_PATH
            (*itr)->SerializeCurrentMovementPath(data);

            // WORLD_PROPERTIES
            (*itr)->SerializeWorldProperties(data);

            // GROUP
            (*itr)->SerializeGroup(data);

            // TEMPLATE - Nothing for player
            //(*itr)->SerializeTemplate(data);

            // COLLECT - Nothing for player
            //(*itr)->SerializeCollect(data);

            // PET
            (*itr)->SerializePet(data);

            // OCCUPATION
            (*itr)->SerializeOccupation(data);

            // XP
            (*itr)->SerializeXP(data);

            // XP_CHARACTERISTICS
            (*itr)->SerializeXPCharacteristics(data);

            // CITIZEN_POINT
            (*itr)->SerializeCitizenPoint(data);

            // GUILD_REMOTE_INFO
            (*itr)->SerializeGuildRemoteInfo(data);

            // NATION_ID
            (*itr)->SerializeNationId(data);

            // NATION_SYNCHRO
            (*itr)->SerializeNationSynchro(data);

            // SOCIAL_STATES
            (*itr)->SerializeSocialStates(data);

            // ACCOUNT_INFORMATION_REMOTE
            (*itr)->SerializeAccountInformationRemote(data);

            // COMPANION_CONTROLLER_ID - Nothing for player
            //(*itr)->SerializeCompanionControllerId(data);

            // VISIBILITY
            (*itr)->SerializeVisibility(data);

            // COSMETICS
            (*itr)->SerializeCosmetics(data);

            // DOWNSCALE_INFO
            (*itr)->SerializeDownscaleInfo(data);
        }
        data.EndBlock<quint16>();
    }

    // On first login send packet with all player/creature around the player
    // For the others send packet to all players around the area

    if (actor)
        sWorld->SendGlobalPacket(data, actor);
    else
        SendPacket(data);
}
