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

    static AuthDatabase* Auth()
    {
        return Database::Instance()->GetAuthDatabase();
    }

    static CharDatabase* Char()
    {
        return Database::Instance()->GetCharDatabase();
    }

    static WorldDatabase* World()
    {
        return Database::Instance()->GetWorldDatabase();
    }

    bool OpenAuthDatabase();
    bool OpenCharDatabase();
    bool OpenWorldDatabase();

private:
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

    AuthDatabase* m_authDatabase;
    CharDatabase* m_charDatabase;
    WorldDatabase* m_worldDatabase;
};

#endif
