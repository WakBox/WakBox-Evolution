#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include "AuthDatabase.h"
#include "CharDatabase.h"
#include "WorldDatabase.h"
#include "Utils/Singleton.h"

class Database : public Singleton<Database>
{
public:
    Database();
    ~Database();

    AuthDatabase* GetAuthDatabase()
    {
        return m_authDatabase;
    }

    CharDatabase* GetCharDatabase()
    {
        return m_charDatabase;
    }

    WorldDatabase* GetWorldDatabase()
    {
        return m_worldDatabase;
    }

    bool OpenAuthDatabase();
    bool OpenCharDatabase();
    bool OpenWorldDatabase();

private:
    AuthDatabase* m_authDatabase;
    CharDatabase* m_charDatabase;
    WorldDatabase* m_worldDatabase;
};

#define sDatabase Database::Instance()
#define sAuthDatabase sDatabase->GetAuthDatabase()
#define sCharDatabase sDatabase->GetCharDatabase()
#define sWorldDatabase sDatabase->GetWorldDatabase()

#endif
