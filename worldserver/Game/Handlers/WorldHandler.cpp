#include "Server/WorldSession.h"
#include "Maps/Map.h"
#include "Entities/ObjectMgr.h"
#include "Utils/Util.h"

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
    QList<Unit*> actorList;
    int i = 0;

    if (actor)
        actorList.push_back(actor->GetCharacter());
    else
    {
        QList<Unit*> mapObjects = GetCharacter()->GetMap()->GetPartitionObjectList(Utils::getIntFromTwoInt(GetCharacter()->GetPositionX(), GetCharacter()->GetPositionY()));

        for (QList<Unit*>::ConstIterator object = mapObjects.begin(); object != mapObjects.end(); ++object)
        {
            if ((*object))
            {
                if ((*object)->GetTypeId() == TYPEID_CHARACTER && (*object)->ToCharacter() == GetCharacter())
                    continue;

                actorList.push_back((*object));
            }
        }
    }

    qDebug() << "Actor list: " << actorList.count();

    WorldPacket data(SMSG_ACTOR_SPAWN);

    data << quint8(0); // 0 = SpawnInWorld, 1= SpawnInMyFight
    data << quint8(actorList.count()); // Actor count

    for (QList<Unit*>::ConstIterator itr = actorList.begin(); itr != actorList.end(); ++itr)
    {
        if ((*itr)->GetTypeId() == TYPEID_CHARACTER)
            data << quint8(0); // Actor type (0 = PlayerCharacter, 1 = NonPlayerCharacter.createNpc, 4 = InteractiveNonPlayerCharacter)
        else
            data << quint8(1);

        data << quint64((*itr)->GetGuid());

        data.StartBlock<quint16>();
        {
            // CharacterSerializerPart
            data << quint8(9); // FOR_REMOTE_CHARACTER_INFORMATION

            if ((*itr)->GetTypeId() == TYPEID_CHARACTER)
            {
                Character* character = (*itr)->ToCharacter();

                if (!character)
                    continue;

                 // ID
                 character->SerializeGuid(data);

                 // IDENTITY
                 character->SerializeIdentity(data);

                 // NAME
                 character->SerializeName(data);

                 // BREED
                 character->SerializeBreed(data);

                 // GUILD_BLAZON
                 character->SerializeGuildBlazon(data);

                 // GUILD_ID
                 character->SerializeGuildId(data);

                 // POSITION
                 character->SerializePosition(data);

                 // APPEARANCE
                 character->SerializeAppearance(data);

                 // PUBLIC_CHARACTERISTICS
                 character->SerializePublicCharacteristics(data);

                 // FIGHT_PROPERTIES
                 character->SerializeFightProperties(data);

                 // FIGHT
                 character->SerializeFight(data);

                 // EQUIPMENT_APPEARANCE
                 character->SerializeEquipmentAppearance(data);

                 // RUNNING_EFFECTS
                 character->SerializeRunningEffects(data);

                 // CURRENT_MOVEMENT_PATH
                 character->SerializeCurrentMovementPath(data);

                 // WORLD_PROPERTIES
                 character->SerializeWorldProperties(data);

                 // GROUP
                 character->SerializeGroup(data);

                 // TEMPLATE - Nothing for player
                 //character->SerializeTemplate(data);

                 // COLLECT - Nothing for player
                 //character->SerializeCollect(data);

                 // PET
                 character->SerializePet(data);

                 // OCCUPATION
                 character->SerializeOccupation(data);

                 // XP
                 character->SerializeXP(data);

                 // XP_CHARACTERISTICS
                 character->SerializeXPCharacteristics(data);

                 // CITIZEN_POINT
                 character->SerializeCitizenPoint(data);

                 // GUILD_REMOTE_INFO
                 character->SerializeGuildRemoteInfo(data);

                 // NATION_ID
                 character->SerializeNationId(data);

                 // NATION_SYNCHRO
                 character->SerializeNationSynchro(data);

                 // SOCIAL_STATES
                 character->SerializeSocialStates(data);

                 // ACCOUNT_INFORMATION_REMOTE
                 character->SerializeAccountInformationRemote(data);

                 // COMPANION_CONTROLLER_ID - Nothing for player
                 //character->SerializeCompanionControllerId(data);

                 // VISIBILITY
                 character->SerializeVisibility(data);

                 // COSMETICS
                 character->SerializeCosmetics(data);

                 // DOWNSCALE_INFO
                 character->SerializeDownscaleInfo(data);
            }
            else if ((*itr)->GetTypeId() == TYPEID_CREATURE)
            {
                Creature* creature = (*itr)->ToCreature();

                if (!creature)
                    continue;

                // ID
                creature->SerializeGuid(data);

                // IDENTITY
                creature->SerializeIdentity(data);

                // NAME
                creature->SerializeName(data);

                // BREED
                creature->SerializeBreed(data);

                // POSITION
                creature->SerializePosition(data);

                // APPEARANCE
                creature->SerializeAppearance(data);

                // TMP
                data << quint16(creature->GetLevel());

                // PUBLIC_CHARACTERISTICS
                creature->SerializePublicCharacteristics(data);

                // FIGHT_PROPERTIES
                creature->SerializeFightProperties(data);

                // FIGHT
                creature->SerializeFight(data);

                // CURRENT_MOVEMENT_PATH
                creature->SerializeCurrentMovementPath(data);

                // WORLD_PROPERTIES
                creature->SerializeWorldProperties(data);

                // GROUP
                creature->SerializeGroup(data);

                // TEMPLATE
                creature->SerializeTemplate(data);

                // COLLECT
                creature->SerializeCollect(data);

                // COMPANION_CONTROLLER_ID
                creature->SerializeCompanionControllerId(data);

            }
        }
        data.EndBlock<quint16>();
    }

    // On first login send packet with all player/creature around the player
    // For the others send packet to all players around the area

    if (actor)
        actor->GetCharacter()->GetMap()->SendPacket(data, actor);
    else
        SendPacket(data);
}
