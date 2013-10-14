#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
#define ADD_OPCODE_HANDLER(opcode, handler) \
    Add(opcode, #opcode, handler);

    // Client messages (CMSG)
    ADD_OPCODE_HANDLER(CMSG_CLIENT_DISCONNECT,                      &WorldSession::HandleNULL);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_VERSION,                         &WorldSession::HandleNULL);
    ADD_OPCODE_HANDLER(CMSG_CLIENT_AUTH,                         &WorldSession::HandleNULL);

    // Server messages (SMSG)
    ADD_OPCODE_HANDLER(SMSG_RSA_PUBLIC_KEY,                         &WorldSession::HandleServerSide);

#undef ADD_OPCODE_HANDLER
}
