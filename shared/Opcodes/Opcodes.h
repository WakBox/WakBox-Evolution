#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

class WorldPacket;
class WorldSession;

enum Opcodes
{
    MSG_UNKNOWN_OPCODE,

    // Client messages (CMSG)

    // Server messages (SMSG)

    NUM_MSG_TYPES
};

struct OpcodeHandler
{
    QString name;
    void (WorldSession::*handler)(WorldPacket& packet);
};

typedef void(WorldSession::*opcodeHandler)(WorldPacket& packet);
typedef QMap<Opcodes, OpcodeHandler> OpcodesList;

class OpcodeTable
{
public:
    static void Load();

    static void Add(quint16 opcode, char const* name, opcodeHandler handler)
    {
        OpcodeHandler opcodeHandler;
        opcodeHandler.name = QString(name);
        opcodeHandler.handler = handler;

        opcodesList.insert(Opcodes(opcode), opcodeHandler);
    }

    static bool Exists(Opcodes id)
    {
        return opcodesList.contains(id);
    }

    static OpcodeHandler Get(Opcodes id)
    {
        return opcodesList.value(id);
    }

private:
    static OpcodesList opcodesList;
};

inline QString GetOpcodeName(Opcodes id)
{
    if (!OpcodeTable::Exists(id))
        return "Unknown opcode";

    return OpcodeTable::Get(id).name;
}

#endif
