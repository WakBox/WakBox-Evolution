#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
#define ADD_OPCODE_HANDLER(opcode, handler) \
    Add(opcode, #opcode, handler);

    // Client messages (CMSG)
    ADD_OPCODE_HANDLER(CMSG_CLIENT_DISCONNECT,                      &WorldSession::HandleNULL);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                         &WorldSession::HandleClientVersion);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_AUTH,                            &WorldSession::HandleClientAuthentication);
    ADD_OPCODE_HANDLER(CMSG_WORLD_SELECT,                           &WorldSession::HandleWorldSelect);
    ADD_OPCODE_HANDLER(CMSG_LEAVE_CHAR_SELECT,                      &WorldSession::HandleLeaveCharSelect);
    ADD_OPCODE_HANDLER(CMSG_CHAR_CREATE,                            &WorldSession::HandleCharCreate);
    ADD_OPCODE_HANDLER(CMSG_CHAR_DELETE,                            &WorldSession::HandleCharDelete);

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RSA_PUBLIC_KEY,                         &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,                     &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_LIST,                             &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_SELECT_RESULT,                    &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAR_LIST,                              &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAR_DELETE_CONFIRM,                    &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_LEAVE_CHAR_SELECT,                      &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_SERVER_TIME,                            &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAR_DELETE,                            &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
