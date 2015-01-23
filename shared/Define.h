#ifndef DEFINE_H
#define DEFINE_H

#define AND &&
#define OR ||

enum TimeConstants
{
    IN_MILLISECONDS = 1000
};

enum StringSize
{
    STRING_SIZE_1 = 0,
    STRING_SIZE_2 = 1,
    STRING_SIZE_4 = 2
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

enum LoginResult
{
    LOGIN_RESULT_SUCCESS                        = 0,
    LOGIN_RESULT_ERROR_INVALID_LOGIN            = 2,
    LOGIN_RESULT_ALREADY_CONNECTED              = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS              = 4,
    LOGIN_RESULT_ERROR_BANNED                   = 5,
    LOGIN_RESULT_ERROR_INTERNAL                 = 7,
    LOGIN_RESULT_ACCOUNT_LOCKED                 = 9,
    LOGIN_RESULT_SERVER_DOWN                    = 10,
    LOGIN_RESULT_TOO_MANY_CONNECTIONS           = 11,
    LOGIN_RESULT_ERROR_INVALID_PARTNER          = 12,
    LOGIN_RESULT_NICKNAME_NOT_SET               = 13,
    LOGIN_RESULT_NICKNAME_INVALID_CONTENT       = 14,
    LOGIN_RESULT_NICKNAME_DUPLICATE             = 15,
    LOGIN_RESULT_NICKNAME_TOO_LONG              = 16,
    LOGIN_RESULT_NICKNAME_TOO_SHORT             = 17,
    LOGIN_RESULT_NICKNAME_EQUALS_LOGIN          = 18,
    LOGIN_RESULT_NICKNAME_ERROR                 = 19,
    LOGIN_RESULT_ERROR_ACCOUNT_INVALID_EMAIL    = 20,
    LOGIN_RESULT_ACCOUNT_UNDER_MODERATION       = 21,
    LOGIN_RESULT_ERROR_OTP_AUTH_FAILED          = 22,
    LOGIN_RESULT_ERROR_EXTERNAL_ACCOUNT_LINKED  = 23,
    LOGIN_RESULT_ERROR_EXTERNAL_NO_ACCOUNT      = 24,
    LOGIN_RESULT_ERROR_FORBIDDEN_COMMUNITY      = 25,
    LOGIN_RESULT_SECURITY_CARD                  = 26,
    LOGIN_RESULT_CLOSED_BETA                    = 127
};

#endif
