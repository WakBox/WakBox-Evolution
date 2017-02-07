#include "Chat.h"
#include "Utils/Util.h"

template<> Chat*  Singleton<Chat>::m_instance = 0;

static ChatCommand commandTable[] =
{
    { "caccount",   SECURITY_ADMINISTRATOR, true, &Chat::HandleAccountCreateCommand, "Create a new account. Syntax : .caccount \"username\" \"pseudo\" \"password\"" },
    { "hello",      SECURITY_ADMINISTRATOR, true, &Chat::HandleHelloCommand,         "Hello world (test command)." },
    { NULL,         0,                      false, NULL,                             NULL }
};

Chat::Chat()
{
    for (quint8 i = 0; commandTable[i].name != NULL; ++i)
        m_chatCommands[commandTable[i].name] = commandTable[i];
}

Chat::~Chat()
{
    m_chatCommands.clear();
}

bool Chat::ParseCommand(QString command)
{
    if (command.left(1) == ".")
    {
        command.remove(0, 1);
        QString commandName = command.split(" ").at(0);

        ChatCommandMap::ConstIterator itr = m_chatCommands.find(commandName);
        if (itr != m_chatCommands.end())
        {
            ChatCommand chatCommand = *itr;
            if (!(this->*chatCommand.Handler)(command))
                Log::Write(LOG_TYPE_NORMAL, chatCommand.description);

            return true;
        }

        Log::Write(LOG_TYPE_NORMAL, "Command \"%s\" don't exist.", commandName.toLatin1().data());
    }

    Log::Write(LOG_TYPE_NORMAL, "Type \".help\" to get full commands list.");
    return false;
}

bool Chat::HandleAccountCreateCommand(QString& args)
{
    QStringList list = args.split(" ");

    if (list.size() < 3)
        return false;

    QString username = list.at(1);
    QString pseudo = list.at(2);
    QString password = list.at(3);

    username.remove("\"");
    pseudo.remove("\"");
    password.remove("\"");

    if (username.isEmpty() || pseudo.isEmpty() || password.isEmpty())
        return false;

    password = Utils::HashPassword(username, password);

    // TODO check if username already exists
    // Email support too...

    QSqlQuery result = sAuthDatabase->Query(INSERT_ACCOUNT, QVariantList() << username << pseudo << password);
    if (result.lastError().number() > QSqlError::NoError)
        return false;

    Log::Write(LOG_TYPE_NORMAL, "The account \"%s\" has been created with success.", username.toLatin1().data());
    return true;
}

bool Chat::HandleHelloCommand(QString& /*args*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Hello World !");
    return true;
}
