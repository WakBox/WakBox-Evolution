#ifndef BINARYDATASTRUCTURE_H
#define BINARYDATASTRUCTURE_H

#include <QtCore>

/**
 * From 1.39.4 - Need to be updated!
 */

struct ChaosParamBinaryData
{
    qint8 m_chaosLevel;
    qint32 m_chaosCollectorParamId;
};

struct TravelLoadingBinaryData
{
    QString m_loadingAnimationName;
    qint32 m_loadingMinDuration;
    qint32 m_loadingFadeInDuration;
    qint32 m_loadingFadeOutDuration;
};

struct AchievementVariableListener
{
    qint32 m_id;
    QString m_successCriterion;
    QList<qint32> m_variableIds;
};

struct AchievementGoal
{
    qint32 m_id;
    bool m_feedback;
    bool m_hasPositionFeedback;
    qint16 m_positionX;
    qint16 m_positionY;
    qint16 m_positionZ;
    qint16 m_positionWorldId;
    QList<AchievementVariableListener> m_vlisteners;
};

struct AchievementReward
{
    qint32 m_id;
    qint32 m_type;
    QList<qint32> m_params;
};

struct AchievementBinaryData
{
    qint32 m_id;
    qint32 m_categoryId;
    bool m_isVisible;
    bool m_notifyOnPass;
    bool m_isActive;
    QString m_criterion;
    QString m_activationCriterion;
    QList<AchievementGoal> m_goals;
    QList<AchievementReward> m_rewards;
    qint32 m_duration;
    qint32 m_cooldown;
    bool m_shareable;
    bool m_repeatable;
    bool m_needsUserAccept;
    qint32 m_recommandedLevel;
    qint32 m_recommandedPlayers;
    bool m_followable;
    qint32 m_displayOnActivationDelay;
    qint64 m_periodStartTime;
    qint64 m_period;
    bool m_autoCompass;
    qint32 m_gfxId;
    bool m_isMercenary;
    qint32 m_mercenaryItemId;
    qint8 m_mercenaryRank;
    qint32 m_order;
};

struct AchievementCategoryBinaryData
{
    qint32 m_id;
    qint32 m_parentId;
};

struct AchievementListData
{
    qint32 m_achievementId;
    qint32 m_order;
};

struct AchievementListBinaryData
{
    qint32 m_id;
    QList<AchievementListData> m_elements;
};

struct AchievementVariableBinaryData
{
    qint32 m_id;
    QString m_name;
    bool m_exportForSteam;
};

struct AlmanachDateBinaryData
{
    qint32 m_id;
    qint64 m_date;
    qint32 m_almanachEntryId;
};

struct AlmanachEntryBinaryData
{
    qint32 m_id;
    qint32 m_scenarioId;
    qint32 m_achievementId;
    QList<qint32> m_territories;
};

struct AptitudeBinaryData
{
    qint32 m_id;
    qint16 m_breedId;
    qint8 m_characteristicId;
    qint32 m_uiId;
    qint32 m_aptitudeGfxId;
    qint32 m_spellGfxId;
    qint16 m_maxLevel;
    qint32 m_constantCost;
    QList<qint32> m_variableCost;
    qint32 m_linkedSpellId;
    QList<qint32> m_levelUnlock;
    QList<qint32> m_effectIds;
};

struct AptitudeBonusBinaryData
{
    qint32 m_bonusId;
    qint32 m_categoryId;
    qint32 m_max;
    qint32 m_gfxId;
    QList<qint32> m_effectIds;
};

struct AptitudeBonusCategoryBinaryData
{
    qint32 m_categoryId;
    QList<qint32> m_levels;
    QList<qint32> m_bonusIds;
};

struct ArcadeChallengeBinaryData
{
    qint32 m_id;
};

struct RankDef
{
    qint32 m_levelOrder;
    qint32 m_scoreMinD;
    qint32 m_scoreMinC;
    qint32 m_scoreMinB;
    qint32 m_scoreMinA;
};

struct Reward
{
    qint32 m_scoreMin;
    qint32 m_itemId;
    qint32 m_xpValue;
    qint8 m_rankNeeded;
};

struct RewardList
{
    qint32 m_id;
    qint32 m_levelOrder;
    QList<Reward> m_rewards;
};

struct Challenge
{
    qint32 m_id;
    float m_ratio;
};

struct ArcadeDungeonBinaryData
{
    qint32 m_id;
    qint16 m_worldId;
    QList<Challenge> m_challenges;
    QList<RewardList> m_rewardsList;
    QList<RankDef> m_ranks;
    qint32 m_scoreRoundBase;
    qint32 m_scoreRoundIncr;
};

struct AreaEffectBinaryData
{
    qint32 m_id;
    qint32 m_scriptId;
    qint32 m_areaAreaId;
    qint32 m_maxExecutionCount;
    qint32 m_targetsToShow;
    bool m_canBeTargeted;
    bool m_obstacleForAI;
    bool m_shouldStopMovement;
    bool m_canBeTargetedByAI;
    bool m_canBeDestroyed;
    QString m_type;
    QList<qint32> m_areaAreaParams;
    QList<qint32> m_applicationTriggers;
    QList<qint32> m_unapplicationTriggers;
    QList<qint32> m_destructionTriggers;
    QList<float> m_deactivationDelay;
    QList<float> m_params;
    QList<qint32> m_properties;
    QList<qint32> m_effectIds;
    QString m_areaGfx;
    QString m_areaCellGfx;
    QString m_aps;
    QString m_cellAps;
    qint32 m_maxLevel;
};

struct AudioMarkerInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_audioMarkerTypeId;
    bool m_isLocalized;
};

struct AvatarBreedBinaryData
{
    qint32 m_id;
    QString m_name;
    qint32 m_backgroundAps;
    qint32 m_baseHp;
    qint32 m_baseAp;
    qint32 m_baseMp;
    qint32 m_baseWp;
    qint32 m_baseInit;
    qint32 m_baseFerocity;
    qint32 m_baseFumble;
    qint32 m_baseWisdom;
    qint32 m_baseTackle;
    qint32 m_baseDodge;
    qint32 m_baseProspection;
    qint32 m_timerCountBeforeDeath;
    qint32 m_preferedArea;
    QList<qint8> m_spellElements;
    QList<float> m_characRatios;
};

struct Color
{
    float m_red;
    float m_green;
    float m_blue;
    float m_alpha;
};

struct Data
{
    qint8 m_sex;
    qint8 m_defaultSkinIndex;
    qint8 m_defaultSkinFactor;
    qint8 m_defaultHairIndex;
    qint8 m_defaultHairFactor;
    qint8 m_defaultPupilIndex;
    QList<Color> m_skinColors;
    QList<Color> m_hairColors;
    QList<Color> m_pupilColors;
};

struct AvatarBreedColorsBinaryData
{
    qint32 m_id;
    QList<Data> m_values;
};

struct Page
{
    qint32 m_id;
    qint16 m_order;
    qint16 m_template;
    qint32 m_imageId;
};

struct BackgroundFeedbackBinaryData
{
    qint32 m_id;
    qint16 m_type;
    QList<Page> m_pages;
};

struct BackgroundInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    qint32 m_backgroundFeedback;
    ChaosParamBinaryData m_chaosParams;
};

struct BagsBinaryData
{
    qint32 m_id;
    qint16 m_capacity;
    qint32 m_bagType;
    QList<qint32> m_validItemCategories;
};

struct BoardInteractiveElementParamBinaryData
{
    qint32 m_id;
};

struct BoatBinaryData
{
    qint32 m_boatId;
    qint32 m_exitX;
    qint32 m_exitY;
    qint32 m_exitWorldId;
    qint32 m_visualId;
    qint32 m_uiGfxId;
    qint8 m_landmarkTravelType;
};

struct BoatLinkBinaryData
{
    qint32 m_id;
    qint32 m_start;
    qint32 m_end;
    qint32 m_cost;
    QString m_criteria;
    QString m_criteriaDisplay;
    bool m_needsToPayEverytime;
    TravelLoadingBinaryData m_loading;
};

struct BookcaseInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint8 m_size;
};

struct Link
{
    qint32 m_id;
    qint32 m_exitX;
    qint32 m_exitY;
    qint32 m_exitWorldId;
    qint32 m_dropWeight;
    QString m_criteria;
    TravelLoadingBinaryData m_loading;
};

struct CannonBinaryData
{
    qint32 m_cannonId;
    qint32 m_visualId;
    qint32 m_uiGfxId;
    qint8 m_landmarkTravelType;
    qint32 m_itemId;
    qint32 m_itemQty;
    QList<Link> m_links;
};

struct CensoredEntryBinaryData
{
    qint32 m_id;
    bool m_deepSearch;
    qint32 m_language;
    qint32 m_censorType;
    QString m_text;
};

struct ChallengeLootEntry
{
    qint32 m_challengeId;
    QString m_criteria;
};

struct ChallengeLootListBinaryData
{
    qint32 m_id;
    QList<ChallengeLootEntry> m_entries;
};

struct CharacGainPerLevelBinaryData
{
    qint16 m_breedId;
    QMap<qint8, float> m_gains;
};

struct CitizenRankBinaryData
{
    qint32 m_id;
    qint32 m_cap;
    qint32 m_pdcLossFactor;
    QString m_translationKey;
    QString m_color;
    QList<qint32> m_rules;
};

struct EventAction
{
    qint32 m_id;
    qint32 m_type;
    QList<QString> m_params;
};

struct EventActionGroup
{
    qint32 m_id;
    qint16 m_dropRate;
    QString m_criterion;
    QList<EventAction> m_actions;
};

struct ClientEventBinaryData
{
    qint32 m_id;
    qint32 m_type;
    qint16 m_dropRate;
    qint16 m_maxCount;
    QString m_criterion;
    QList<QString> m_filters;
    bool m_activeOnStart;
    QList<EventActionGroup> m_actionGroups;
};

struct ClimateBonusBinaryData
{
    qint32 m_buffId;
    qint32 m_gfxId;
    QString m_criteria;
    qint32 m_duration;
    qint16 m_price;
    float m_temperatureDifference;
    float m_rainDifference;
    float m_windDifference;
};

struct ClimateBonusListBinaryData
{
    qint32 m_buffListId;
    QList<qint32> m_entries;
};

struct CollectItem
{
    qint32 m_uid;
    qint32 m_itemId;
    qint32 m_qty;
};

struct CollectAction
{
    qint32 m_actionId;
    qint32 m_actionType;
    QList<QString> m_params;
    QString m_criteria;
};

struct CollectInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    qint16 m_capacity;
    bool m_locked;
    qint32 m_cashQty;
    QList<CollectItem> m_items;
    QList<CollectAction> m_actions;
};

struct CompanionItemBinaryData
{
    qint32 m_id;
};

struct CraftBinaryData
{
    qint32 m_craftId;
    qint32 m_bookItemId;
    float m_xpFactor;
    bool m_innate;
    bool m_conceptualCraft;
    bool m_hiddenCraft;
};

struct CraftInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_apsId;
    qint32 m_visualMruId;
    qint32 m_skillId;
    QList<qint32> m_allowedRecipes;
    ChaosParamBinaryData m_chaosParams;
};

struct DecorationInteractiveElementParamBinaryData
{
    qint32 m_id;
    QList<qint32> m_havreGemTypes;
};

struct DestructibleElementParamBinaryData
{
    qint32 m_id;
    qint32 m_pdv;
    qint32 m_regenDelay;
    qint32 m_resWater;
    qint32 m_resFire;
    qint32 m_resEarth;
    qint32 m_resWind;
    QList<qint32> m_effectIds;
};

struct Answer
{
    qint32 m_id;
    QString m_criterion;
    qint32 m_type;
    bool m_clientOnly;
};

struct DialogBinaryData
{
    qint32 m_id;
    QString m_criteria;
    QList<Answer> m_answers;
};

struct DoorInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    bool m_consumeItem;
    qint32 m_itemNeeded;
    qint32 m_kamaCost;
    QString m_criterion;
};

struct DragoBinaryData
{
    qint32 m_dragoId;
    qint32 m_exitX;
    qint32 m_exitY;
    qint32 m_visualId;
    qint32 m_uiGfxId;
    QString m_dragoCriterion;
    qint8 m_landmarkTravelType;
    TravelLoadingBinaryData m_loading;
};

struct DungeonBinaryData
{
    qint32 m_id;
    qint16 m_minLevel;
    qint16 m_instanceId;
    QList<qint32> m_tps;
};

struct DungeonDisplayerInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_dungeonId;
};

struct EffectGroupBinaryData
{
    qint32 m_id;
    QList<qint32> m_effectIds;
};

struct EmoteBinaryData
{
    qint32 m_id;
    qint16 m_type;
    QString m_cmd;
    bool m_needTarget;
    bool m_moveToTarget;
    bool m_infiniteDuration;
    bool m_isMusical;
    QList<QString> m_scriptParams;
};

struct EquipableDummyInteractiveElementParamBinaryData
{
    qint32 m_id;
    QString m_animName;
    qint8 m_sex;
};

struct Consumable
{
    qint32 m_itemId;
    qint16 m_quantity;
};

struct Resulting
{
    qint32 m_itemId;
    qint16 m_quantity;
    qint8 m_forcedBindType;
};

struct Exchange
{
    qint32 m_exchangeId;
    QString m_criteria;
    QList<Consumable> m_consumables;
    qint32 m_consumableKama;
    qint32 m_consumablePvpMoney;
    QList<Resulting> m_resultings;
    qint32 m_resultingKama;
};

struct ExchangeInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_apsId;
    qint32 m_visualMruId;
    qint8 m_sortTypeId;
    QList<Exchange> m_exchanges;
    ChaosParamBinaryData m_chaosParams;
};

struct FightChallengeReward
{
    qint32 m_id;
    QString m_criterion;
    qint16 m_xpLevel;
    qint16 m_dropLevel;
};

struct FightChallengeBinaryData
{
    qint32 m_id;
    qint32 m_dropWeight;
    QString m_dropCriterion;
    qint32 m_stateId;
    qint32 m_listenedEffectSuccess;
    qint32 m_listenedEffectFailure;
    qint32 m_gfxId;
    bool m_isBase;
    QList<qint32> m_incompatibleChallenges;
    QList<qint32> m_incompatibleMonsters;
    QList<FightChallengeReward> m_rewards;
};

struct FightChallengeMonsterBinaryData
{
    qint32 m_id;
    qint16 m_randomRolls;
    qint16 m_forcedRolls;
    QList<qint32> m_forcedChallenges;
};

struct GemAndPowderBinaryData
{
    qint32 m_id;
};

struct GemBackgroundInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_backgroundFeedback;
    QList<qint32> m_havreGemTypes;
};

struct Action
{
    qint32 m_actionId;
    qint32 m_actionTypeId;
    QString m_criteria;
    QList<QString> m_actionParams;
};

struct GroupAction
{
    qint32 m_id;
    QString m_criteria;
    float m_weight;
    QList<Action> m_actions;
};

struct Visual
{
    qint32 m_id;
    qint32 m_visualId;
    qint32 m_itemConsumed;
    qint32 m_itemQuantity;
    bool m_doConsumeItem;
    qint32 m_kamaCost;
    qint32 m_distributionDuration;
    QList<GroupAction> m_groupActions;
};

struct GenericActivableInteractiveElementParamBinaryData
{
    qint32 m_id;
    QList<Visual> m_visuals;
    ChaosParamBinaryData m_chaosParams;
};

struct GroundBinaryData
{
    qint32 m_id;
    QMap<qint32, short> m_resourceFertility;
    QMap<qint16, qint16> m_resourceTypeFertility;
};

struct HavenBagModelViewBinaryData
{
    qint32 m_id;
    bool m_restrictionWorld;
    bool m_restrictionMarket;
    qint32 m_backgroundMapId;
    bool m_innate;
};

struct HavenWorldBoardInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    qint16 m_havenWorldId;
    qint16 m_miniOriginCellX;
    qint16 m_miniOriginCellY;
    qint16 m_miniOriginCellZ;
};

struct Interactive
{
    qint32 m_uid;
    qint32 m_templateId;
    qint8 m_x;
    qint8 m_y;
    qint8 m_z;
};

struct Skin
{
    qint32 m_itemId;
    qint32 m_editorGroupId;
};

struct WorldEffect
{
    qint32 m_buffId;
};

struct HavenWorldBuildingBinaryData
{
    qint32 m_id;
    qint16 m_catalogEntryId;
    qint32 m_kamaCost;
    qint32 m_ressourceCost;
    qint8 m_workersGranted;
    qint8 m_workers;
    qint32 m_editorGroupId;
    bool m_canBeDestroyed;
    QList<Interactive> m_interactives;
    QList<Skin> m_skins;
    QList<qint32> m_effectIds;
    QList<WorldEffect> m_worldEffects;
};

struct BuildingCondition
{
    qint32 m_buildingTypeNeeded;
    qint32 m_quantity;
};

struct HavenWorldBuildingCatalogBinaryData
{
    qint32 m_id;
    qint32 m_order;
    qint32 m_buildingType;
    qint32 m_categoryId;
    bool m_buyable;
    qint16 m_maxQuantity;
    bool m_isDecoOnly;
    qint32 m_buildingSoundId;
    QList<BuildingCondition> m_buildingCondition;
};

struct HavenWorldBuildingDecoBinaryData
{
    qint32 m_id;
    qint16 m_catalogEntryId;
    qint32 m_kamaCost;
    qint32 m_ressourceCost;
    qint32 m_editorGroupId;
};

struct HavenWorldBuildingEvolutionBinaryData
{
    qint32 m_id;
    qint16 m_catalogEntryId;
    qint32 m_fromId;
    qint32 m_toId;
    qint64 m_delay;
    qint8 m_order;
};

struct VisualElement
{
    qint32 m_uid;
    qint32 m_gfxId;
    bool m_hasGuildColor;
    bool m_occluder;
    qint8 m_height;
    QString m_animName;
    qint8 m_direction;
    qint8 m_x;
    qint8 m_y;
    qint8 m_z;
};

struct HavenWorldBuildingVisualDefinitionBinaryData
{
    qint32 m_id;
    qint32 m_buildingId;
    QList<VisualElement> m_elements;
};

struct HavenWorldDefinitionBinaryData
{
    qint32 m_id;
    qint16 m_worldId;
    qint8 m_workers;
    qint16 m_exitWorldId;
    qint16 m_exitCellX;
    qint16 m_exitCellY;
    qint16 m_exitCellZ;
};

struct HavenWorldPatchDefinitionBinaryData
{
    qint32 m_id;
    qint32 m_patchId;
    qint32 m_kamaCost;
    qint32 m_categoryId;
    qint32 m_soundId;
};

struct InstanceInteractionLevelBinaryData
{
    qint32 m_id;
    qint32 m_worldId;
    qint32 m_subscriptionLevel;
    qint32 m_interactionLevel;
};

struct InteractiveElementModelBinaryData
{
    qint32 m_id;
    qint16 m_type;
    qint32 m_gfx;
    qint32 m_color;
    qint8 m_height;
    qint32 m_particleId;
    qint32 m_particleOffsetZ;
};

struct Point3
{
    qint32 m_x;
    qint32 m_y;
    qint16 m_z;
};

struct InteractiveElementTemplateBinaryData
{
    qint32 m_id;
    qint16 m_modelType;
    qint16 m_worldId;
    qint32 m_x;
    qint32 m_y;
    qint16 m_z;
    qint16 m_initialState;
    bool m_initiallyVisible;
    bool m_initiallyUsable;
    bool m_blockingMovement;
    bool m_blockingLos;
    qint8 m_direction;
    qint16 m_activationPattern;
    QString m_parameter;
    qint32 m_templateId;
    QList<qint32> m_properties;
    QList<Point3> m_positionsTrigger;
    QMap<qint16, qint32> m_actions;
    QList<qint32> m_views;
};

struct ItemAction
{
    qint32 m_actionId;
    qint32 m_actionTypeId;
    bool m_consumeItemOnAction;
    bool m_clientOnly;
    bool m_stopMovement;
    bool m_hasScript;
    QString m_criteria;
    QList<QString> m_actionParams;
    QList<QString> m_actionScriptParams;
};

struct ItemBinaryData
{
    qint32 m_id;
    qint32 m_metaId;
    qint16 m_itemSetId;
    qint32 m_gfxId;
    qint32 m_femaleGfxId;
    qint32 m_floorGfxId;
    qint16 m_level;
    QList<QString> m_criteria;
    qint32 m_itemTypeId;
    qint16 m_maxStackHeight;
    qint8 m_useCostAP;
    qint8 m_useCostMP;
    qint8 m_useCostFP;
    qint32 m_useRangeMin;
    qint32 m_useRangeMax;
    bool m_useTestFreeCell;
    bool m_useTestNotBorderCell;
    bool m_useTestLos;
    bool m_useTestOnlyLine;
    qint16 m_itemRarity;
    qint8 m_itemBindType;
    QString m_generationType;
    QList<qint32> m_itemProperties;
    qint8 m_itemActionVisual;
    qint8 m_worldUsageTarget;
    qint8 m_gemElementType;
    qint8 m_gemNum;
    QList<qint32> m_effectIds;
    QList<ItemAction> m_actions;
    QList<qint32> m_subMetaIds;
    QList<qint8> m_gemSlots;
    QList<qint8> m_gemSlotType;
};

struct ItemSetBinaryData
{
    qint16 m_id;
    qint32 m_linkedItemReferenceId;
    QList<qint32> m_itemsId;
    QMap<qint32, QList<qint32>> m_effectIdsByPartCount;
};

struct ItemTypeBinaryData
{
    qint16 m_id;
    qint16 m_parentId;
    bool m_visibleInAnimations;
    bool m_visibleInMarketPlace;
    bool m_recyclable;
    QList<QString> m_equipmentPosition;
    QList<QString> m_disabledEquipementPosition;
    qint16 m_materialType;
    QList<qint32> m_craftIds;
};

struct KrosmozFigureBinaryData
{
    qint32 m_id;
    qint32 m_year;
    qint32 m_addon;
    qint32 m_season;
};

struct KrosmozGameBoardInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint8 m_gameId;
};

struct KrosmozGameCollectionInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint8 m_gameId;
};

struct LootEntry
{
    qint32 m_itemId;
    qint16 m_quantity;
    qint16 m_quantityPerItem;
};

struct LightLootListBinaryData
{
    qint32 m_id;
    QList<LootEntry> m_entries;
};

struct LockBinaryData
{
    qint32 m_id;
    qint32 m_lockedItemId;
    qint32 m_lockValue;
    qint64 m_periodDuration;
    qint64 m_unlockDate;
    bool m_availableForCitizensOnly;
};

struct LootChestInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    qint32 m_cooldown;
    qint32 m_cost;
    qint32 m_itemIdCost;
    qint32 m_itemQuantityCost;
    bool m_doConsumeItem;
    qint32 m_nbActivation;
    qint32 m_distributionDuration;
    QString m_criteria;
    ChaosParamBinaryData m_chaosParams;
};

struct MagiCraftLootEntry
{
    qint32 m_itemId;
};

struct MagiCraftLootListBinaryData
{
    qint32 m_id;
    qint8 m_gemType;
    QList<MagiCraftLootEntry> m_entries;
};

struct MarketBoardInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualMruId;
    qint32 m_marketId;
    ChaosParamBinaryData m_chaosParams;
};

struct SpellInfo
{
    qint32 m_id;
    qint32 m_level;
};

struct Equipement
{
    QString m_fileId;
    QList<QString> m_parts;
};

struct MonsterColor
{
    qint32 m_partIndex;
    qint32 m_color;
};

struct Anim
{
    qint8 m_key;
    QString m_animName;
};

struct MonsterCollectActionData
{
    qint32 m_id;
    qint32 m_skillId;
    qint32 m_skillLevelRequired;
    qint32 m_skillVisualFeedbackId;
    QString m_criteria;
    float m_xpFactor;
    qint32 m_collectLootListId;
    qint32 m_duration;
    qint32 m_collectItemId;
    QList<qint32> m_lootList;
    bool m_displayInCraftDialog;
};

struct MonsterAction
{
    qint32 m_id;
    qint8 m_type;
    QString m_criteria;
    bool m_criteriaOnNpc;
    bool m_moveToMonsterBeforeInteractWithHim;
    qint32 m_duration;
    bool m_showProgressBar;
    qint32 m_visualId;
    qint32 m_scriptId;
};

struct MonsterBehaviourData
{
    qint32 m_id;
    qint32 m_type;
    qint32 m_scriptId;
    bool m_needsToWaitPathEnd;
};

struct MonsterEvolutionData
{
    qint32 m_id;
    qint32 m_breedId;
    qint32 m_scriptId;
};

struct MonsterBinaryData
{
    qint32 m_id;
    qint32 m_familyId;
    qint16 m_levelMin;
    qint16 m_levelMax;
    float m_xpMultiplicator;
    float m_arcadePointsMultiplicator;
    qint32 m_baseHp;
    qint32 m_baseWp;
    qint32 m_baseAp;
    qint32 m_baseMp;
    qint32 m_baseRange;
    qint32 m_baseInit;
    qint32 m_basePerception;
    qint32 m_baseParade;
    qint32 m_baseWill;
    qint32 m_baseCriticalHit;
    qint32 m_baseTimeBeforeDeath;
    float m_HpInc;
    float m_WpInc;
    float m_ApInc;
    float m_MpInc;
    float m_rangeInc;
    float m_initInc;
    float m_perceptionInc;
    float m_paradeInc;
    float m_willInc;
    float m_CriticalHitInc;
    qint32 m_baseHealingBonus;
    qint32 m_baseSummonBonus;
    qint32 m_baseMechanicsBonus;
    qint32 m_baseTackleBonus;
    qint32 m_baseFireDamageBonus;
    qint32 m_baseWaterDamageBonus;
    qint32 m_baseEarthDamageBonus;
    qint32 m_baseWindDamageBonus;
    qint32 m_baseFireResistance;
    qint32 m_baseWaterResistance;
    qint32 m_baseEarthResistance;
    qint32 m_baseWindResistance;
    qint32 m_baseTackleResistance;
    qint32 m_baseAPLossResistance;
    qint32 m_basePMLossResistance;
    qint32 m_baseWPLossResistance;
    float m_healingBonusInc;
    float m_tackleBonusInc;
    float m_fireDamageBonusInc;
    float m_waterDamageBonusInc;
    float m_earthDamageBonusInc;
    float m_windDamageBonusInc;
    float m_fireResistanceInc;
    float m_waterResistanceInc;
    float m_earthResistanceInc;
    float m_windResistanceInc;
    float m_tackleResistanceInc;
    float m_apLossResistanceInc;
    float m_pmLossResistanceInc;
    float m_wpLossResistanceInc;
    bool m_hasDeadEvolution;
    qint16 m_npcRank;
    qint16 m_agroRadius;
    qint16 m_sightRadius;
    qint32 m_radiusSize;
    QList<qint32> m_fightProperties;
    QList<qint32> m_worldProperties;
    QList<qint16> m_naturalStates;
    QList<SpellInfo> m_spellsIdAndLevel;
    qint8 m_familyRank;
    qint16 m_walkingSpeed;
    qint16 m_runningSpeed;
    qint16 m_runningRadiusInWorld;
    qint16 m_runningRadiusInFight;
    QList<MonsterAction> m_monsterActionData;
    QList<MonsterCollectActionData> m_monsterCollectActionData;
    QList<MonsterBehaviourData> m_monsterBehaviourData;
    QList<MonsterEvolutionData> m_monsterEvolutionData;
    qint32 m_requiredLeadershipPoints;
    qint16 m_alignmentId;
    qint32 m_timelineBuffId;
    qint32 m_monsterHeight;
    qint32 m_defeatScriptId;
    QList<qint32> m_gfxEquipment;
    QList<Equipement> m_specialGfxEquipement;
    QList<MonsterColor> m_specialGfxColor;
    QList<Anim> m_specialGfxAnim;
    qint32 m_gfx;
    qint32 m_timelineGfx;
};

struct MonsterTypeBinaryData
{
    qint32 m_id;
    qint32 m_parentId;
    qint8 m_type;
};

struct MonsterTypeDungeonBinaryData
{
    qint32 m_id;
    qint32 m_familyId;
    qint32 m_dungeonId;
    qint16 m_level;
};

struct MonsterTypePestBinaryData
{
    qint32 m_id;
    qint32 m_familyId;
    qint32 m_pestMonsterId;
};

struct MonsterTypeRelashionshipBinaryData
{
    qint32 m_id;
    qint32 m_familyFrom;
    qint32 m_familyTo;
};

struct NationColorsBinaryData
{
    qint32 m_id;
    QString m_color;
};

struct NationLawBinaryData
{
    qint32 m_id;
    qint32 m_lawConstantId;
    QList<QString> m_params;
    qint32 m_basePointsModification;
    qint32 m_percentPointsModification;
    qint32 m_lawPointCost;
    bool m_lawLocked;
    bool m_applicableToCitizen;
    bool m_applicableToAlliedForeigner;
    bool m_applicableToNeutralForeigner;
    QList<qint32> m_restrictedNations;
};

struct NationRankBinaryData
{
    qint32 m_id;
    float m_citizenPointLossFactor;
    QString m_criteria;
    qint32 m_citizenScoreLine;
};

struct HealthPenalty
{
    qint8 m_penaltyType;
    qint8 m_value;
};

struct HealthItem
{
    qint32 m_itemId;
    qint32 m_value;
};

struct MealItem
{
    qint32 m_itemId;
    bool m_visible;
};

struct SleepItem
{
    qint32 m_itemId;
    qint64 m_duration;
};

struct ColorItem
{
    qint32 m_itemId;
    qint32 m_partId;
    qint32 m_colorABGR;
};

struct ReskinItem
{
    qint32 m_itemId;
    qint32 m_gfxId;
};

struct PetBinaryData
{
    qint32 m_id;
    qint32 m_itemRefId;
    qint32 m_gfxId;
    qint32 m_itemColorRefId;
    qint32 m_itemReskinRefId;
    qint32 m_health;
    qint64 m_minMealInterval;
    qint64 m_maxMealInterval;
    qint8 m_xpByMeal;
    qint16 m_xpPerLevel;
    qint16 m_levelMax;
    qint8 m_mountType;
    QList<HealthPenalty> m_healthPenalties;
    QList<HealthItem> m_healthItems;
    QList<MealItem> m_mealItems;
    QList<SleepItem> m_sleepItems;
    QList<qint32> m_equipmentItems;
    QList<ColorItem> m_colorItems;
    QList<ReskinItem> m_reskinItems;
};

struct ProtectorFaunaWill
{
    qint32 m_typeId;
    qint16 m_min;
    qint16 m_max;
};

struct ProtectorFloraWill
{
    qint32 m_typeId;
    qint16 m_min;
    qint16 m_max;
};

struct ProtectorSecret
{
    qint32 m_id;
    qint32 m_achievementGoalId;
    qint32 m_secretGfxId;
    qint32 m_discoveredGfxId;
};

struct ProtectorBinaryData
{
    qint32 m_protectorId;
    qint32 m_monsterId;
    qint32 m_buffListId;
    qint32 m_buffListIdToBuy;
    qint32 m_scenarioLootListId;
    qint32 m_scenarioLootListIdToBuy;
    qint32 m_scenarioLootListIdChaos;
    qint32 m_scenarioLootListIdEcosystem;
    qint32 m_climateListIdToBuy;
    qint32 m_nationId;
    qint32 m_territory;
    qint32 m_fightStake;
    qint32 m_positionX;
    qint32 m_positionY;
    qint16 m_positionZ;
    QList<qint32> m_craftLearnt;
    QList<ProtectorSecret> m_secrets;
    QList<ProtectorFaunaWill> m_faunaWill;
    QList<ProtectorFloraWill> m_floraWill;
};

struct ProtectorBuffBinaryData
{
    qint32 m_buffId;
    qint32 m_gfxId;
    QString m_criteria;
    qint8 m_origin;
    QList<qint32> m_effects;
};

struct ProtectorBuffListBinaryData
{
    qint32 m_buffListId;
    QList<qint32> m_buffLists;
};

struct ProtectorFaunaProtection
{
    qint32 m_monsterFamilyId;
    qint32 m_protectionCost;
    qint32 m_reintroductionCost;
    qint32 m_reintroductionItemId;
    qint16 m_reintroductionItemQty;
};

struct ProtectorFloraProtection
{
    qint32 m_resourceFamilyId;
    qint32 m_protectionCost;
    qint32 m_reintroductionCost;
    qint32 m_reintroductionItemId;
    qint16 m_reintroductionItemQty;
};

struct ProtectorEcosystemProtectionBinaryData
{
    qint32 m_protectorId;
    QList<ProtectorFaunaProtection> m_faunaProtection;
    QList<ProtectorFloraProtection> m_floraProtection;
};

struct RecipeIngredient
{
    qint32 m_itemId;
    qint16 m_quantity;
};

struct RecipeProduct
{
    qint32 m_itemId;
    qint16 m_quantity;
};

struct RecipeMaterial
{
    qint16 m_minLevel;
    qint16 m_minRarity;
    bool m_optionnal;
    QList<qint32> m_materialTypes;
};

struct RecipeBinaryData
{
    qint32 m_id;
    qint32 m_categoryId;
    qint64 m_duration;
    QString m_criteria;
    QString m_visibilityCriteria;
    qint32 m_level;
    QList<qint32> m_properties;
    qint32 m_xpRatio;
    QList<qint32> m_machinesUsingRecipe;
    qint32 m_successRate;
    bool m_contractEnabled;
    qint64 m_neededKamas;
    qint64 m_xp;
    QList<RecipeIngredient> m_ingredients;
    QList<RecipeProduct> m_products;
    QList<RecipeMaterial> m_materials;
};

struct RecycleMachineInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_visualMruId;
    ChaosParamBinaryData m_chaosParams;
};

struct ResourceStepAction
{
    qint32 m_id;
    qint32 m_skillId;
    qint32 m_resourceNextIndex;
    qint32 m_skillLevelRequired;
    qint32 m_skillSimultaneousPlayer;
    qint32 m_skillVisualFeedbackId;
    qint32 m_duration;
    qint32 m_consumableId;
    qint32 m_gfxId;
    QString m_criteria;
    qint32 m_collectLootListId;
    qint32 m_collectItemId;
    QList<qint32> m_lootItems;
    qint32 m_mruOrder;
    bool m_displayInCraftDialog;
};

struct ResourceStep
{
    qint32 m_index;
    QList<ResourceStepAction> m_actions;
    qint32 m_sizeCategoryId;
    qint32 m_lightRadius;
    qint32 m_lightColor;
    qint32 m_apsId;
    qint32 m_apsPosZ;
};

struct ResourceBinaryData
{
    qint32 m_id;
    qint32 m_type;
    qint16 m_idealRainMin;
    qint16 m_idealRainMax;
    qint16 m_idealTemperatureMin;
    qint16 m_idealTemperatureMax;
    bool m_isBlocking;
    bool m_useBigChallengeAps;
    bool m_isMonsterEmbryo;
    qint16 m_monsterStepHatching;
    QList<qint32> m_properties;
    QList<qint32> m_monsterFamilies;
    QList<ResourceStep> m_steps;
    qint16 m_height;
    qint32 m_iconGfxId;
    QMap<qint32, QList<qint32>> m_gfxIds;
};

struct RewardDisplayerInteractiveElementParamBinaryData
{
    qint32 m_id;
    QList<qint32> m_itemIds;
};

struct SecretBinaryData
{
    qint32 m_id;
    qint16 m_level;
    qint16 m_itemId;
};

struct SkillActionBinaryData
{
    qint32 m_id;
    qint32 m_mruGfxId;
    QString m_mruKey;
    QList<qint32> m_associatedItems;
    QString m_animLinkage;
};

struct SkillBinaryData
{
    qint32 m_id;
    qint32 m_type;
    qint32 m_scriptId;
    qint32 m_mruGfxId;
    QString m_mruKey;
    QString m_animLinkage;
    QList<qint32> m_associatedItemTypes;
    QList<qint32> m_associatedItems;
    qint32 m_maxLevel;
    bool m_isInnate;
};

struct CustomCharac
{
    qint32 m_base;
    float m_increment;
};

struct CastParam
{
    QMap<qint8, CustomCharac> m_costs;
    qint32 m_cost;
    float m_PA_base;
    float m_PA_inc;
    float m_PM_base;
    float m_PM_inc;
    float m_PW_base;
    float m_PW_inc;
    float m_rangeMinBase;
    float m_rangeMinInc;
    float m_rangeMaxBase;
    float m_rangeMaxInc;
    bool m_isLosAware;
    bool m_onlyInLine;
    bool m_rangeIsDynamic;
};

struct SpellBinaryData
{
    qint32 m_id;
    qint32 m_scriptId;
    qint32 m_gfxId;
    qint16 m_maxLevel;
    qint16 m_breedId;
    qint16 m_castMaxPerTarget;
    float m_castMaxPerTurn;
    float m_castMaxPerTurnIncr;
    qint16 m_castMinInterval;
    bool m_testLineOfSight;
    bool m_castOnlyLine;
    bool m_castOnlyInDiag;
    bool m_testFreeCell;
    bool m_testNotBorderCell;
    bool m_testDirectPath;
    qint32 m_targetFilter;
    QString m_castCriterion;
    float m_PA_base;
    float m_PA_inc;
    float m_PM_base;
    float m_PM_inc;
    float m_PW_base;
    float m_PW_inc;
    float m_rangeMaxBase;
    float m_rangeMaxInc;
    float m_rangeMinBase;
    float m_rangeMinLevelIncrement;
    qint16 m_maxEffectCap;
    qint16 m_element;
    qint16 m_xpGainPercentage;
    qint16 m_spellType;
    qint16 m_uiPosition;
    QString m_learnCriteria;
    qint8 m_passive;
    bool m_useAutomaticDescription;
    bool m_showInTimeline;
    bool m_canCastWhenCarrying;
    qint8 m_actionOnCriticalMiss;
    bool m_spellCastRangeIsDynamic;
    bool m_castSpellWillBreakInvisibility;
    bool m_castOnRandomCell;
    bool m_tunnelable;
    bool m_canCastOnCasterCell;
    bool m_associatedWithItemUse;
    QList<qint32> m_properties;
    QList<qint32> m_effectIds;
    QMap<qint8, CustomCharac> m_baseCastParameters;
    QMap<QString, CastParam> m_alternativeCasts;
};

struct StateBinaryData
{
    qint32 m_id;
    qint16 m_maxLevel;
    QList<qint32> m_endTrigger;
    QList<qint32> m_duration;
    QList<float> m_durationInc;
    bool m_endsAtEndOfTurn;
    bool m_isDurationInFullTurns;
    bool m_inTurnInFight;
    bool m_isReplacable;
    bool m_isTransmigrable;
    QString m_hmiActions;
    QString m_applyCriterion;
    bool m_isCumulable;
    bool m_durationInCasterTurn;
    bool m_durationInRealTime;
    QList<qint32> m_effectIds;
    QList<qint32> m_stateImmunities;
    bool m_stateShouldBeSaved;
    bool m_decursable;
    qint8 m_stateType;
    qint8 m_statePowerType;
    bool m_isReapplyEvenAtMaxLevel;
    bool m_timelineVisible;
    qint32 m_gfxId;
    bool m_displayCasterName;
};

struct StaticEffectBinaryData
{
    qint32 m_effectId;
    qint32 m_actionId;
    qint32 m_parentId;
    qint16 m_areaOrderingMethod;
    QList<qint32> m_areaSize;
    qint16 m_areaShape;
    qint16 m_emptyCellsAreaOrderingMethod;
    QList<qint32> m_emptyCellsAreaSize;
    qint16 m_emptyCellsAreaShape;
    QList<qint32> m_triggersBeforeComputation;
    QList<qint32> m_triggersBeforeExecution;
    QList<qint32> m_triggersForUnapplication;
    QList<qint32> m_triggersAfterExecution;
    QList<qint32> m_triggersAfterAllExecutions;
    QList<qint32> m_triggersNotRelatedToExecutions;
    QList<qint32> m_triggersAdditionnal;
    QString m_criticalState;
    QList<qint64> m_targetValidator;
    bool m_affectedByLocalisation;
    qint32 m_durationBase;
    float m_durationInc;
    bool m_endsAtEndOfTurn;
    bool m_isDurationInFullTurns;
    qint16 m_applyDelayBase;
    float m_applyDelayIncrement;
    QList<float> m_params;
    float m_probabilityBase;
    float m_probabilityInc;
    qint8 m_triggerListenerType;
    qint8 m_triggerTargetType;
    qint8 m_triggerCasterType;
    bool m_storeOnSelf;
    qint16 m_maxExecution;
    float m_maxExecutionIncr;
    qint8 m_maxTargetCount;
    bool m_isFightEffect;
    QString m_hmiAction;
    qint16 m_containerMinLevel;
    qint16 m_containerMaxLevel;
    QString m_effectCriterion;
    QString m_effectParentType;
    QString m_effectContainerType;
    bool m_dontTriggerAnything;
    bool m_isPersonal;
    bool m_isDecursable;
    bool m_notifyInChatForCaster;
    bool m_notifyInChatForTarget;
    bool m_notifyInChatWithCasterName;
    qint32 m_scriptFileId;
    bool m_durationInCasterTurn;
    QList<qint32> m_effectProperties;
    bool m_displayInSpellDescription;
    bool m_displayInStateBar;
    bool m_recomputeAreaOfEffectDisplay;
    bool m_isInTurnInFight;
    bool m_notifyInChat;
};

struct StoolInteractiveElementParamBinaryData
{
    qint32 m_id;
    QString m_criterion;
    qint32 m_visualId;
    ChaosParamBinaryData m_chaosParams;
};

struct Compartment
{
    qint32 m_uid;
    qint32 m_boxId;
    qint32 m_unlockItemId;
    qint8 m_capacity;
    qint32 m_compartmentOrder;
};

struct StorageBoxBinaryData
{
    qint32 m_id;
    qint32 m_visualId;
    ChaosParamBinaryData m_chaosParams;
    QList<Compartment> m_compartments;
};

struct StreetLightInteractiveElementParamBinaryData
{
    qint32 m_id;
    qint32 m_color;
    float m_range;
    qint32 m_apsId;
    bool m_activeOnlyInNight;
    qint32 m_ignitionVisualId;
    bool m_ignitionUseObject;
    qint32 m_ignitionDuration;
    qint32 m_extinctionVisualId;
    bool m_extinctionUseObject;
    qint32 m_extinctionDuration;
    ChaosParamBinaryData m_chaosParams;
};

struct Destination
{
    qint32 m_destinationId;
    qint32 m_x;
    qint32 m_y;
    qint32 m_z;
    qint32 m_worldId;
    qint8 m_direction;
    QString m_criteria;
    qint32 m_visualId;
    qint32 m_apsId;
    qint16 m_delay;
    qint32 m_itemConsumed;
    qint16 m_itemQuantity;
    qint16 m_kamaCost;
    bool m_doConsumeItem;
    bool m_isInvisible;
    QString m_loadingAnimationName;
    qint32 m_loadingMinDuration;
    qint32 m_loadingFadeInDuration;
    qint32 m_loadingFadeOutDuration;
};

struct TeleporterBinaryData
{
    qint32 m_teleporterId;
    qint32 m_lockId;
    QList<Destination> m_destinations;
};

struct TimelineBuffListBinaryData
{
    qint32 m_id;
    qint32 m_typeId;
    qint32 m_gfxId;
    bool m_forPlayer;
    QList<qint32> m_effectIds;
};

struct TreasureBinaryData
{
    qint32 m_id;
    qint32 m_usedItem;
    qint32 m_rewardItem;
    qint16 m_quantity;
    qint32 m_rewardKama;
    qint32 m_rewardLootChest;
    qint32 m_duration;
    QString m_criterion;
    float m_winPercent;
};

struct Event
{
    qint32 m_eventId;
};

struct TutorialBinaryData
{
    qint32 m_id;
    QList<Event> m_eventIds;
};

struct ZaapBinaryData
{
    qint32 m_zaapId;
    qint32 m_exitX;
    qint32 m_exitY;
    qint32 m_exitWorldId;
    qint32 m_visualId;
    qint32 m_uiGfxId;
    qint8 m_landmarkTravelType;
    bool m_zaapBase;
    QString m_destinationCriteria;
    TravelLoadingBinaryData m_loading;
};

struct ZaapLinkBinaryData
{
    qint32 m_id;
    qint32 m_start;
    qint32 m_end;
    qint32 m_cost;
};

#endif // BINARYDATASTRUCTURE_H
