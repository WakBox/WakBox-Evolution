#ifndef SHAREDDEFINES_H
#define SHAREDDEFINES_H

enum CharacterCreationResult
{
    CHARACTER_CREATION_RESULT_SUCCESS = 0,
    CHARACTER_CREATION_RESULT_FAILED = 1,
    CHARACTER_CREATION_RESULT_NAME_EXISTS = 10,
    CHARACTER_CREATION_RESULT_INVALID_NAME = 11,
    CHARACTER_CREATION_RESULT_TOO_MANY_CHARACTERS = 12
};

enum CharacterBreed
{
    CHARACTER_BREED_NONE            = 0,
    CHARACTER_BREED_FECA            = 1,
    CHARACTER_BREED_OSAMOAD         = 2,
    CHARACTER_BREED_ENUTROF         = 3,
    CHARACTER_BREED_SRAM            = 4,
    CHARACTER_BREED_XELOR           = 5,
    CHARACTER_BREED_ECAFLIP         = 6,
    CHARACTER_BREED_ENIRIPSA        = 7,
    CHARACTER_BREED_IOP             = 8,
    CHARACTER_BREED_CRA             = 9,
    CHARACTER_BREED_SADIDA          = 10,
    CHARACTER_BREED_SACRIER         = 11,
    CHARACTER_BREED_PANDAWA         = 12,
    CHARACTER_BREED_ROGUE           = 13,
    CHARACTER_BREED_MASQUERAIDER    = 14,
    CHARACTER_BREED_FOGGERNAUT      = 16,
    CHARACTER_BREED_TUTORIAL        = 17
};

enum Nations
{
    NATION_NONE                     = 0,
    NATION_AMAKNA                   = 30,
    NATION_BONTA                    = 31,
    NATION_BRAKMAR                  = 32,
    NATION_SUFOKIA                  = 33
};


enum InteractiveElementType
{
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE                   = 0,
    INTERACTIVE_ELEMENT_TYPE_TURN_ON                    = 1,
    INTERACTIVE_ELEMENT_TYPE_TURN_OFF                   = 2,
    INTERACTIVE_ELEMENT_TYPE_PUSH                       = 3,
    INTERACTIVE_ELEMENT_TYPE_PULL                       = 4,
    INTERACTIVE_ELEMENT_TYPE_WALKON                     = 5,
    INTERACTIVE_ELEMENT_TYPE_SITON                      = 6,
    INTERACTIVE_ELEMENT_TYPE_STANDUP                    = 7,
    INTERACTIVE_ELEMENT_TYPE_NONE                       = 8,
    INTERACTIVE_ELEMENT_TYPE_WALKIN                     = 9,
    INTERACTIVE_ELEMENT_TYPE_WALKOUT                    = 10,
    INTERACTIVE_ELEMENT_TYPE_ENTER                      = 11,
    INTERACTIVE_ELEMENT_TYPE_START_BROWSING             = 12,
    INTERACTIVE_ELEMENT_TYPE_STOP_BROWSING              = 13,
    INTERACTIVE_ELEMENT_TYPE_START_MANAGE               = 14,
    INTERACTIVE_ELEMENT_TYPE_STOP_MANAGE                = 15,
    INTERACTIVE_ELEMENT_TYPE_CONFIRM_COLLECT            = 16,
    INTERACTIVE_ELEMENT_TYPE_OPEN                       = 17,
    INTERACTIVE_ELEMENT_TYPE_CLOSE                      = 18,
    INTERACTIVE_ELEMENT_TYPE_LOCK                       = 19,
    INTERACTIVE_ELEMENT_TYPE_UNLOCK                     = 20,
    INTERACTIVE_ELEMENT_TYPE_DISCONNECT_AND_ACTIVATE    = 21,
    INTERACTIVE_ELEMENT_TYPE_CHALLENGE_ACTIVATE         = 22,
    INTERACTIVE_ELEMENT_TYPE_REPACK                     = 23,
    INTERACTIVE_ELEMENT_TYPE_REGISTER                   = 24,
    INTERACTIVE_ELEMENT_TYPE_VOTE                       = 25,
    INTERACTIVE_ELEMENT_TYPE_RECYCLE                    = 26,
    INTERACTIVE_ELEMENT_TYPE_MOVE                       = 27,
    INTERACTIVE_ELEMENT_TYPE_READ                       = 28,
    INTERACTIVE_ELEMENT_TYPE_ROTATE                     = 29,
    INTERACTIVE_ELEMENT_TYPE_ASK_INFORMATIONS           = 30,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE2                  = 31,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE3                  = 32,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE4                  = 33,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE5                  = 34,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE6                  = 35,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE7                  = 36,
    INTERACTIVE_ELEMENT_TYPE_ACTIVATE8                  = 37
};

#endif
