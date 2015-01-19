#ifndef DEFINE_H
#define DEFINE_H

#define AND &&
#define OR ||

enum TimeConstants
{
    IN_MILLISECONDS = 1000
};

enum Community
{
    COMMUNITY_FR    = 0,
    COMMUNITY_UK    = 1,
    COMMUNITY_INT   = 2,
    COMMUNITY_DE    = 3,
    COMMUNITY_ES    = 4,
    COMMUNITY_RU    = 5,
    COMMUNITY_PT    = 6,
    COMMUNITY_NL    = 7,
    COMMUNITY_JP    = 8,
    COMMUNITY_IT    = 9,
    COMMUNITY_NA    = 11,
    COMMUNITY_CN    = 12,
    COMMUNITY_ASIA  = 13,
    COMMUNITY_TW    = 14,
};

enum StringSize
{
    STRING_SIZE_1 = 0,
    STRING_SIZE_2 = 1,
    STRING_SIZE_4 = 2
};

#endif
