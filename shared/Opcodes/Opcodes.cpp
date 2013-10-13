#include "Opcodes.h"
#include "Server/WorldSession.h"

OpcodesList OpcodeTable::opcodesList;

void OpcodeTable::Load()
{
    #define ADD_OPCODE_HANDLER(opcode, handler) \
        Add(opcode, #opcode, handler);

    ADD_OPCODE_HANDLER(MSG_UNKNOWN_OPCODE, &WorldSession::HandleNULL);

    // Client messages (CMSG)

    // Server messages (SMSG)
}
