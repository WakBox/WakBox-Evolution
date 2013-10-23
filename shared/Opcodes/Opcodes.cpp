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

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RSA_PUBLIC_KEY,                         &WorldSession::HandleServerSide);
    ADD_OPCODE_HANDLER(SMSG_CLIENT_AUTH_RESULT,                     &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
