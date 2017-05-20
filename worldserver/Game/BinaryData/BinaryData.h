#ifndef BINARYDATA_H
#define BINARYDATA_H

#include "BinaryDataStructure.h"
#include "BinaryData/BinaryDataStorage.h"

#include "Storage/AchievementStorage.h"

extern AchievementStorage<AchievementBinaryData> sAchievement;

void LoadBinaryStorage();

#endif // BINARYDATA_H
