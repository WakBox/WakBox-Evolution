#ifndef BINARYDATA_MONSTERSTORAGE_H
#define BINARYDATA_MONSTERSTORAGE_H

#include "BinaryData/BinaryDataStorage.h"

template<class T>
class MonsterStorage : public BinaryDataStorage<T>
{
public:
    MonsterStorage() { }

    void Load()
    {
        qint32 size = this->m_rows.size();

        for (qint32 i = 0; i < size; ++i)
        {
            Row row = this->m_rows[i];
            this->_reader->SetBufferPosition(row.offset);

            MonsterBinaryData entry;

            entry.m_id = this->_reader->ReadInt();
            entry.m_familyId = this->_reader->ReadInt();
            entry.m_levelMin = this->_reader->ReadShort();
            entry.m_levelMax = this->_reader->ReadShort();
            entry.m_xpMultiplicator = this->_reader->ReadFloat();
            entry.m_arcadePointsMultiplicator = this->_reader->ReadFloat();
            entry.m_baseHp = this->_reader->ReadInt();
            entry.m_baseWp = this->_reader->ReadInt();
            entry.m_baseAp = this->_reader->ReadInt();
            entry.m_baseMp = this->_reader->ReadInt();
            entry.m_baseRange = this->_reader->ReadInt();
            entry.m_baseInit = this->_reader->ReadInt();
            entry.m_basePerception = this->_reader->ReadInt();
            entry.m_baseParade = this->_reader->ReadInt();
            entry.m_baseWill = this->_reader->ReadInt();
            entry.m_baseCriticalHit = this->_reader->ReadInt();
            entry.m_baseTimeBeforeDeath = this->_reader->ReadInt();
            entry.m_HpInc = this->_reader->ReadFloat();
            entry.m_WpInc = this->_reader->ReadFloat();
            entry.m_ApInc = this->_reader->ReadFloat();
            entry.m_MpInc = this->_reader->ReadFloat();
            entry.m_rangeInc = this->_reader->ReadFloat();
            entry.m_initInc = this->_reader->ReadFloat();
            entry.m_perceptionInc = this->_reader->ReadFloat();
            entry.m_paradeInc = this->_reader->ReadFloat();
            entry.m_willInc = this->_reader->ReadFloat();
            entry.m_CriticalHitInc = this->_reader->ReadFloat();
            entry.m_baseHealingBonus = this->_reader->ReadInt();
            entry.m_baseSummonBonus = this->_reader->ReadInt();
            entry.m_baseMechanicsBonus = this->_reader->ReadInt();
            entry.m_baseTackleBonus = this->_reader->ReadInt();
            entry.m_baseFireDamageBonus = this->_reader->ReadInt();
            entry.m_baseWaterDamageBonus = this->_reader->ReadInt();
            entry.m_baseEarthDamageBonus = this->_reader->ReadInt();
            entry.m_baseWindDamageBonus = this->_reader->ReadInt();
            entry.m_baseFireResistance = this->_reader->ReadInt();
            entry.m_baseWaterResistance = this->_reader->ReadInt();
            entry.m_baseEarthResistance = this->_reader->ReadInt();
            entry.m_baseWindResistance = this->_reader->ReadInt();
            entry.m_baseTackleResistance = this->_reader->ReadInt();
            entry.m_baseAPLossResistance = this->_reader->ReadInt();
            entry.m_basePMLossResistance = this->_reader->ReadInt();
            entry.m_baseWPLossResistance = this->_reader->ReadInt();
            entry.m_healingBonusInc = this->_reader->ReadFloat();
            entry.m_tackleBonusInc = this->_reader->ReadFloat();
            entry.m_fireDamageBonusInc = this->_reader->ReadFloat();
            entry.m_waterDamageBonusInc = this->_reader->ReadFloat();
            entry.m_earthDamageBonusInc = this->_reader->ReadFloat();
            entry.m_windDamageBonusInc = this->_reader->ReadFloat();
            entry.m_fireResistanceInc = this->_reader->ReadFloat();
            entry.m_waterResistanceInc = this->_reader->ReadFloat();
            entry.m_earthResistanceInc = this->_reader->ReadFloat();
            entry.m_windResistanceInc = this->_reader->ReadFloat();
            entry.m_tackleResistanceInc = this->_reader->ReadFloat();
            entry.m_apLossResistanceInc = this->_reader->ReadFloat();
            entry.m_pmLossResistanceInc = this->_reader->ReadFloat();
            entry.m_wpLossResistanceInc = this->_reader->ReadFloat();
            entry.m_hasDeadEvolution = this->_reader->ReadBool();
            entry.m_npcRank = this->_reader->ReadShort();
            entry.m_agroRadius = this->_reader->ReadShort();
            entry.m_sightRadius = this->_reader->ReadShort();
            entry.m_radiusSize = this->_reader->ReadInt();
            entry.m_fightProperties = this->_reader->ReadIntArray();
            entry.m_worldProperties = this->_reader->ReadIntArray();
            entry.m_naturalStates = this->_reader->ReadShortArray();

            qint32 spellsIdAndLevelCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < spellsIdAndLevelCount; ++i)
            {
                SpellInfo spellInfo;

                spellInfo.m_id = this->_reader->ReadInt();
                spellInfo.m_level = this->_reader->ReadInt();

                entry.m_spellsIdAndLevel.push_back(spellInfo);
            }

            entry.m_familyRank = this->_reader->ReadByte();
            entry.m_walkingSpeed = this->_reader->ReadShort();
            entry.m_runningSpeed = this->_reader->ReadShort();
            entry.m_runningRadiusInWorld = this->_reader->ReadShort();
            entry.m_runningRadiusInFight = this->_reader->ReadShort();

            qint32 monsterActionDataCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < monsterActionDataCount; ++i)
            {
                MonsterAction monsterAction;

                monsterAction.m_id = this->_reader->ReadInt();
                monsterAction.m_type = this->_reader->ReadByte();
                monsterAction.m_criteria = this->_reader->ReadString();
                monsterAction.m_criteriaOnNpc = this->_reader->ReadBool();
                monsterAction.m_moveToMonsterBeforeInteractWithHim = this->_reader->ReadBool();
                monsterAction.m_duration = this->_reader->ReadInt();
                monsterAction.m_showProgressBar = this->_reader->ReadBool();
                monsterAction.m_visualId = this->_reader->ReadInt();
                monsterAction.m_scriptId = this->_reader->ReadInt();

                entry.m_monsterActionData.push_back(monsterAction);
            }


            qint32 monsterCollectActionDataCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < monsterCollectActionDataCount; ++i)
            {
                MonsterCollectActionData monsterCollectActionData;

                monsterCollectActionData.m_id = this->_reader->ReadInt();
                monsterCollectActionData.m_skillId = this->_reader->ReadInt();
                monsterCollectActionData.m_skillLevelRequired = this->_reader->ReadInt();
                monsterCollectActionData.m_skillVisualFeedbackId = this->_reader->ReadInt();
                monsterCollectActionData.m_criteria = this->_reader->ReadString();
                monsterCollectActionData.m_xpFactor = this->_reader->ReadFloat();
                monsterCollectActionData.m_collectLootListId = this->_reader->ReadInt();
                monsterCollectActionData.m_duration = this->_reader->ReadInt();
                monsterCollectActionData.m_collectItemId = this->_reader->ReadInt();
                monsterCollectActionData.m_lootList = this->_reader->ReadIntArray();
                monsterCollectActionData.m_displayInCraftDialog = this->_reader->ReadBool();

                entry.m_monsterCollectActionData.push_back(monsterCollectActionData);
            }


            qint32 monsterBehaviourDataCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < monsterBehaviourDataCount; ++i)
            {
                MonsterBehaviourData monsterBehaviourData;

                monsterBehaviourData.m_id = this->_reader->ReadInt();
                monsterBehaviourData.m_type = this->_reader->ReadInt();
                monsterBehaviourData.m_scriptId = this->_reader->ReadInt();
                monsterBehaviourData.m_needsToWaitPathEnd = this->_reader->ReadBool();

                entry.m_monsterBehaviourData.push_back(monsterBehaviourData);
            }


            qint32 monsterEvolutionDataCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < monsterEvolutionDataCount; ++i)
            {
                MonsterEvolutionData monsterEvolutionData;

                monsterEvolutionData.m_id = this->_reader->ReadInt();
                monsterEvolutionData.m_breedId = this->_reader->ReadInt();
                monsterEvolutionData.m_scriptId = this->_reader->ReadInt();

                entry.m_monsterEvolutionData.push_back(monsterEvolutionData);
            }

            entry.m_requiredLeadershipPoints = this->_reader->ReadInt();
            entry.m_alignmentId = this->_reader->ReadShort();
            entry.m_timelineBuffId = this->_reader->ReadInt();
            entry.m_monsterHeight = this->_reader->ReadInt();
            entry.m_defeatScriptId = this->_reader->ReadInt();
            entry.m_gfxEquipment = this->_reader->ReadIntArray();

            qint32 specialGfxEquipementCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < specialGfxEquipementCount; ++i)
            {
                Equipement equipement;

                equipement.m_fileId = this->_reader->ReadString();
                equipement.m_parts = this->_reader->ReadStringArray();

                entry.m_specialGfxEquipement.push_back(equipement);
            }


            qint32 specialGfxColorCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < specialGfxColorCount; ++i)
            {
                Color color;

                color.m_partIndex = this->_reader->ReadInt();
                color.m_color = this->_reader->ReadInt();

                entry.m_specialGfxColor.push_back(color);
            }


            qint32 specialGfxAnimCount = this->_reader->ReadInt();

            for (qint32 i = 0; i < specialGfxAnimCount; ++i)
            {
                Anim anim;

                anim.m_key = this->_reader->ReadByte();
                anim.m_animName = this->_reader->ReadString();

                entry.m_specialGfxAnim.push_back(anim);
            }

            entry.m_gfx = this->_reader->ReadInt();
            entry.m_timelineGfx = this->_reader->ReadInt();

            this->m_entries[entry.m_id] = entry;
        }

        qDebug() << ">> Loaded " << this->m_entries.size() << " entries for MonsterStorage";
    }
};

#endif // BINARYDATA_MONSTERSTORAGE_H
