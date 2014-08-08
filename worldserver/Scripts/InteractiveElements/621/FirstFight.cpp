#include "Game/Scripting/ScriptMgr.h"

class InteractiveElement_Tutorial_FirstFight : InteractiveElementScript
{
public:
    InteractiveElement_Tutorial_FirstFight() : InteractiveElementScript("InteractiveElement_Tutorial_FirstFight")
    {
        m_spawned = false;
    }

    void OnActive(Character* character, InteractiveElementType /*type*/)
    {
        // Envoie comme quoi l'élémentId n'est plus "usable" (différence avec le paquet de spawn 200)
        WorldPacket data(SMSG_INTERACTIVE_ELEMENT_UPDATE);

        data << quint64(20114); // Instance ElementId

        data.StartBlock<quint16>();
        {
            data << quint8(1); // BlockCount

            data << quint8(2); // blockId
            data << quint32(6); // offset

            data << quint8(2); // BlockId

            data << quint16(1); // ?
            data << quint8(1); // isVisible
            data << quint8(0); // isUsable
            data << quint8(0); // ?
            data << quint8(0); // ?
            data << quint8(0); // ?
            data << quint32(0); // ?
        }
        data.EndBlock<quint16>();

        character->GetSession()->SendPacket(data);

        // Spawn Wapin
        WorldPacket data2(SMSG_UPDATE_OBJECT);
        data2 << quint8(0);
        data2 << quint8(1);

        data2 << quint8(1);
        data2 << qint64(-1706442045669898);

        data2.StartBlock<quint16>();
        {
            data2 << quint8(7);

            // GUID
            data2 << qint64(-1706442045669898);

            // IDENTITY
            data2 << quint8(1);
            data2 << qint64(-1);

            // NAME
            data2 << quint16(0);

            // BREED
            data2 << quint16(2644);

            // POSITION
            data2 << qint32(0); // X
            data2 << qint32(-17); // Y
            data2 << qint16(0); // Z
            data2 << quint16(-1); // InstanceId
            data2 << quint8(1); // Direction

            // APPEARANCE
            data2 << quint8(1); // Show

            // PUBLIC_CHARACTERISTICS
            data2 << quint16(1); // Level
            data2 << quint16(0); // States size

            // FIGHT_PROPERTIES
            data2 << quint8(0); // hasProperties

            // FIGHT
            data2 << qint32(-1); // currentFightId
            data2 << quint8(0); // isKo
            data2 << quint8(0); // isDead
            data2 << quint8(0); // isSummoned
            data2 << quint8(0); // isFleeing
            data2 << qint8(-1); // obstacleId
            data2 << quint8(0); // hasSummon

            // EQUIPMENT_APPEARANCE
            data2 << quint8(0); // size

            // RUNNING_EFFECTS
            data2 << quint8(1); // hasInFightData
            data2 << quint16(1); // data size
            data2 << quint8(13); // data

            data2 << quint8(1); // hasOutFightData
            data2 << quint16(0); // size

            // CURRENT_MOVEMENT_PATH
            data2 << quint8(0); // hasCurrentPath

            // WORLD_PROPERTIES
            data2 << quint8(0); // hasProperties

            // GROUP
            data2 << quint64(79645873605204); // PartyId
            data2 << quint16(1); // Members size
            data2 << qint16(-1); // breedId
            data2 << qint16(-1); // Level

            // TEMPLATE
            data2 << quint16(0); // sightRadius
            data2 << quint16(0); // aggroRadius

            // COLLECT
            data2 << quint16(0);

            // OCCUPATION
            data2 << quint8(0);

            // XP
            data2 << quint64(0);

            // XP_CHARACTERISTICS
            data2 << quint16(0);
            data2 << quint16(0);
            data2 << quint16(0);
            data2 << quint32(0);

            // Pourquoi sniff size 110 et la on est déjà à 117 ??            
        }
        data2.EndBlock<quint16>();

        character->GetSession()->SendPacket(data2);

        // Activation du script (mouvement de la fenêtre entre autre)
        WorldPacket data3(SMSG_SCENARIO_SCRIPT);
        data3 << quint8(0); // Event
        data3 << quint32(12603); // Function
        data3 << quint32(1611); // ScenarioId
        data3 << quint8(1); // Long size?
        data3 << qint64(-1706442045669898); // Param
        character->GetSession()->SendPacket(data3);

        // Spawn Kano
        WorldPacket data4(SMSG_UPDATE_OBJECT);
        data4 << quint8(0);
        data4 << quint8(1);

        data4 << quint8(1);
        data4 << qint64(-1706442045669878);

        data4.StartBlock<quint16>();
        {
            data4 << quint8(7);

            // GUID
            data4 << qint64(-1706442045669878);

            // IDENTITY
            data4 << quint8(1);
            data4 << qint64(-1);

            // NAME
            data4 << quint16(0);

            // BREED
            data4 << quint16(2694);

            // POSITION
            data4 << qint32(0); // X
            data4 << qint32(-21); // Y
            data4 << qint16(3); // Z
            data4 << quint16(-1); // InstanceId
            data4 << quint8(3); // Direction

            // APPEARANCE
            data4 << quint8(1); // Show

            // PUBLIC_CHARACTERISTICS
            data4 << quint16(100); // Level
            data4 << quint16(0); // States size

            // FIGHT_PROPERTIES
            data4 << quint8(0); // hasProperties

            // FIGHT
            data4 << qint32(-1); // currentFightId
            data4 << quint8(0); // isKo
            data4 << quint8(0); // isDead
            data4 << quint8(0); // isSummoned
            data4 << quint8(0); // isFleeing
            data4 << qint8(-1); // obstacleId
            data4 << quint8(0); // hasSummon

            // EQUIPMENT_APPEARANCE
            data4 << quint8(0); // size

            // RUNNING_EFFECTS
            data4 << quint8(1); // hasInFightData
            data4 << quint16(2); // data size
            data4 << quint8(13); // data
            data4 << quint8(1); // data

            data4 << quint8(1); // hasOutFightData
            data4 << quint16(0); // size

            // CURRENT_MOVEMENT_PATH
            data4 << quint8(0); // hasCurrentPath

            // WORLD_PROPERTIES
            data4 << quint8(0); // hasProperties

            // GROUP
            data4 << quint64(79645873605204); // PartyId
            data4 << quint16(1); // Members size
            data4 << qint16(-1); // breedId
            data4 << qint16(-1); // Level

            // TEMPLATE
            data4 << quint16(0); // sightRadius
            data4 << quint16(0); // aggroRadius

            // COLLECT
            data4 << quint16(0);

            // OCCUPATION
            data4 << quint8(0);

            // XP
            data4 << quint64(0);

            // XP_CHARACTERISTICS
            data4 << quint16(0);
            data4 << quint16(0);
            data4 << quint16(0);
            data4 << quint32(0);

            // Pourquoi sniff size 110 et la on est déjà à 117 ??
        }
        data4.EndBlock<quint16>();

        character->GetSession()->SendPacket(data4);

        m_spawned = true;
    }

    void OnUpdate(quint64 diff)
    {
    }

private:
    bool m_spawned;
};

void AddScript_InteractiveElement_Tutorial_FirstFight()
{
    new InteractiveElement_Tutorial_FirstFight();
}
