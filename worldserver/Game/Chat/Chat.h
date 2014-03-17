#ifndef CHAT_H
#define CHAT_H

#include <QtCore>

#include "Utils/Singleton.h"
#include "Logs/Log.h"

class Chat;

enum ChatSecurity
{
    SECURITY_PLAYER = 0,
    SECURITY_MODERATOR = 1,
    SECURITY_GAMEMASTER = 2,
    SECURITY_ADMINISTRATOR = 3
};

struct ChatCommand
{
    QString name;
    quint8 security;
    bool allowConsole;
    bool (Chat::*Handler)(QString& args);
    QString description;
};

typedef QMap<QString, ChatCommand> ChatCommandMap;

class Chat : public Singleton<Chat>
{
public:
    Chat();
    ~Chat();

    bool ParseCommand(QString command);

    // Commands handlers
    bool HandleAccountCreateCommand(QString& args);
    bool HandleHelloCommand(QString& args);

private:
    ChatCommandMap m_chatCommands;
};

#endif
