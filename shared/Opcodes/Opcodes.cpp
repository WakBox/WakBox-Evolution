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

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RSA_PUBLIC_KEY,                         &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,                     &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_LIST,                             &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_WORLD_SELECT_RESULT,                    &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CHAR_LIST,                              &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_SERVER_TIME,                            &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
