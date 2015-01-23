#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
    #define ADD_OPCODE_HANDLER(opcode, status, handler) \
        Add(opcode, #opcode, status, handler);

    // Client messages (CMSG)
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                         STATUS_ALWAYS,      &WorldSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_PUBLIC_KEY_REQUEST,                     STATUS_ALWAYS,      &WorldSession::HandlePublicKeyRequest);
    ADD_OPCODE_HANDLER(CMSG_AUTH_TOKEN,                             STATUS_ALWAYS,      &WorldSession::HandleClientAuthToken);
    ADD_OPCODE_HANDLER(CMSG_AUTH_TOKEN_REQUEST,                     STATUS_AUTHED,      &WorldSession::HandleAuthTokenRequest);

    //    ADD_OPCODE_HANDLER(CMSG_PING_COMMAND,                           &WorldSession::HandlePingCommand);
    //    ADD_OPCODE_HANDLER(CMSG_INTERACTIVE_ELEMENT,                    &WorldSession::HandleInteractiveElement);
    //    ADD_OPCODE_HANDLER(CMSG_GROUP_INVITE,                           &WorldSession::HandleGroupInvite);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_SELECT,                            &WorldSession::HandleCharSelect);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_DELETE,                            &WorldSession::HandleCharDelete);
    //    ADD_OPCODE_HANDLER(CMSG_LEAVE_CHAR_SELECT,                      &WorldSession::HandleLeaveCharSelect);
    //    ADD_OPCODE_HANDLER(CMSG_WHOIS_COMMAND,                          &WorldSession::HandleWhoisCommand);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_CREATE,                            &WorldSession::HandleCharCreate);
    //    ADD_OPCODE_HANDLER(CMSG_CHAT_MESSAGE,                           &WorldSession::HandleChatMessage);
    //    ADD_OPCODE_HANDLER(CMSG_PRIVATE_MESSAGE,                        &WorldSession::HandlePrivateMessage);
    //    ADD_OPCODE_HANDLER(CMSG_TRADE_MESSAGE,                          &WorldSession::HandleTradeMessage);
    //    ADD_OPCODE_HANDLER(CMSG_RECRUIT_MESSAGE,                        &WorldSession::HandleRecruitMessage);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_MOVEMENT,                          &WorldSession::HandleCharMovement);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_DIRECTION,                         &WorldSession::HandleCharDirection);
    //    ADD_OPCODE_HANDLER(CMSG_CHAR_EMOTE,                             &WorldSession::HandleCharEmote);
    //    ADD_OPCODE_HANDLER(CMSG_START_FIGHT,                            &WorldSession::HandleStartFight);
    //    ADD_OPCODE_HANDLER(CMSG_SWITCH_CHAR,                            &WorldSession::HandleSwitchChar);
    //    ADD_OPCODE_HANDLER(CMSG_CLIENT_LANGUAGE,                        &WorldSession::HandleClientLanguage);
    //    ADD_OPCODE_HANDLER(CMSG_SERVER_TIME_COMMAND,                    &WorldSession::HandleServerTimeCommand);

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_CLIENT_VERSION_RESULT,                  STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_IP,                              STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,                     STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_PUBLIC_KEY_RESULT,                      STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_SELECT_RESULT,                    STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAR_LIST,                              STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_CALENDAR_SYNC,                   STATUS_NEVER,       &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_SYSTEM_CONFIGURATION,                   STATUS_UNHANDLED,   &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_ADDITIONAL_CHARACTER_SLOTS_UPDATE,      STATUS_UNHANDLED,   &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_FREE_COMPANION_BREED_ID,                STATUS_UNHANDLED,   &WorldSession::HandleServerSide);
    // TEMP STATUS_AUTHED because same opcode than a CMSG (MSG support or status check change)
    ADD_OPCODE_HANDLER(SMSG_AUTH_TOKEN_RESULT,                      STATUS_AUTHED,      &WorldSession::HandleServerSide);


    //    ADD_OPCODE_HANDLER(SMSG_PING_COMMAND,                           &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_INTERACTIVE_ELEMENT_SPAWN,              &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_INTERACTIVE_ELEMENT_UPDATE,             &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHAR_SELECT,                            &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHAR_DELETE,                            &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHAR_CREATE,                            &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_LEAVE_CHAR_SELECT,                      &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_WHOIS_COMMAND,                          &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHAT_MESSAGE,                           &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHARACTER_STATS_ENTER_WORLD,            &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_SEND_CHARACTER_POSITION,                &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_UPDATE_OBJECT,                          &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_UPDATE_CREATURE_STATE,                  &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_CHAR_DIRECTION,                         &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_SEND_CHAR_POSITION,                     &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_UPDATE_POSITION,                        &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_PROPERTIES_UPDATE,                      &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_START_FIGHT,                            &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_SCENARIO_SCRIPT,                        &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_SERVER_TIME_COMMAND,                    &WorldSession::HandleServerSide);
    //    ADD_OPCODE_HANDLER(SMSG_ENTER_WORLD,                            &WorldSession::HandleServerSide);

    #undef ADD_OPCODE_HANDLER
}
