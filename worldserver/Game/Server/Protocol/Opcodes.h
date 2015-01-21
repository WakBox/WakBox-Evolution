#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

enum Opcodes
{
    // Client messages (CMSG)
    CMSG_PING_COMMAND                           = 107,
    CMSG_INTERACTIVE_ELEMENT                    = 201,
    CMSG_GROUP_INVITE                           = 501,
    CMSG_CHAR_SELECT                            = 2049,
    CMSG_CHAR_DELETE                            = 2051,
    CMSG_CHAR_CREATE                            = 2053,
    CMSG_LEAVE_CHAR_SELECT                      = 2055,
    CMSG_WHOIS_COMMAND                          = 2060,
    CMSG_CHAT_MESSAGE                           = 3153,
    CMSG_PRIVATE_MESSAGE                        = 3155,
    CMSG_TRADE_MESSAGE                          = 3159,
    CMSG_RECRUIT_MESSAGE                        = 3167,
    CMSG_CHAR_MOVEMENT                          = 4113,
    CMSG_CHAR_DIRECTION                         = 4117,
    CMSG_CHAR_EMOTE                             = 4119,
    CMSG_START_FIGHT                            = 4529,
    CMSG_SWITCH_CHAR                            = 11003,
    CMSG_CLIENT_LANGUAGE                        = 13001,
    CMSG_SERVER_TIME_COMMAND                    = 15000,

    // Server messages (SMSG)
    SMSG_CONNECTION_RETRY_TICKET                = 2,
    SMSG_PING_COMMAND                           = 108,
    SMSG_INTERACTIVE_ELEMENT_SPAWN              = 200,
    SMSG_INTERACTIVE_ELEMENT_UPDATE             = 202,
    SMSG_WORLD_LIST                             = 1200,
    SMSG_WORLD_SELECT_RESULT                    = 1202,
    SMSG_CHAR_LIST                              = 2048,
    SMSG_CHAR_SELECT                            = 2050,
    SMSG_CHAR_DELETE                            = 2052,
    SMSG_CHAR_CREATE                            = 2054,
    SMSG_LEAVE_CHAR_SELECT                      = 2056,
    SMSG_WHOIS_COMMAND                          = 2061,
    SMSG_SERVER_TIME                            = 2063,
    SMSG_CHAT_MESSAGE                           = 3152,
    SMSG_CHARACTER_STATS_ENTER_WORLD            = 4098,
    SMSG_SEND_CHARACTER_POSITION                = 4100,
    SMSG_UPDATE_OBJECT                          = 4102,
    SMSG_UPDATE_CREATURE_STATE                  = 4112,
    SMSG_CHAR_DIRECTION                         = 4118,
    SMSG_SEND_CHAR_POSITION                     = 4125,
    SMSG_UPDATE_POSITION                        = 4127,
    SMSG_PROPERTIES_UPDATE                      = 4130,
    SMSG_START_FIGHT                            = 4530,
    SMSG_SCENARIO_SCRIPT                        = 11100,
    SMSG_SERVER_TIME_COMMAND                    = 15001,
    SMSG_ENTER_WORLD                            = 20002
};

enum SessionStatus
{
    STATUS_UNHANDLED = 0,       // Opcode not handled
    STATUS_ALWAYS,              // Opcode always accepted
    STATUS_NEVER,               // Opcode not accepted from client (deprecated or server side only)
    STATUS_AUTHED,              // Player authenticated
    STATUS_IN_WORLD,            // Player in world
    STATUS_TRANSFER             // Player transferring (not in world)
};

class WorldPacket;
class WorldSession;

struct OpcodeHandler
{
    QString name;
    SessionStatus status;
    void (WorldSession::*handler)(WorldPacket& packet);
};

typedef void(WorldSession::*opcodeHandler)(WorldPacket& packet);
typedef QMap<Opcodes, OpcodeHandler> OpcodesList;

class OpcodeTable
{
public:
    static void Load();

    static void Add(quint16 opcode, char const* name, SessionStatus status, opcodeHandler handler)
    {
        OpcodeHandler opcodeHandler;
        opcodeHandler.name = QString(name);
        opcodeHandler.status = status;
        opcodeHandler.handler = handler;

        opcodesList.insert(Opcodes(opcode), opcodeHandler);
    }

    static bool Exists(quint16 id)
    {
        return opcodesList.contains((Opcodes)id);
    }

    static OpcodeHandler Get(quint16 id)
    {
        return opcodesList.value((Opcodes)id);
    }

private:
    static OpcodesList opcodesList;
};

inline QString GetOpcodeName(quint16 id)
{
    if (!OpcodeTable::Exists(id))
        return "Unknown opcode";

    return OpcodeTable::Get(id).name;
}

#endif