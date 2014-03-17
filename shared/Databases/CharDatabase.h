#ifndef CHARDATABASE_H
#define CHARDATABASE_H

#include <QtCore>
#include "MysqlConnection.h"

class CharDatabase : public MysqlConnection
{
public:
    CharDatabase(ConnectionInfo& connectionInfo) : MysqlConnection(connectionInfo) {}

    virtual void LoadQueries();
};

enum CharDatabaseQueries
{    
    /**
     * DATABASE_STATEMENT_SUMMARY
     */
    SELECT_CHARACTER_MAX_GUID,
    SELECT_CHARACTERS_BY_ACCOUNT_ID,
    SELECT_CHARACTER_BY_GUID,
    SELECT_CHARACTER_BY_GUID_AND_ACCOUNT,
    SELECT_CHARACTER_BY_NAME,
    DELETE_CHARACTER_BY_GUID,
    INSERT_CHARACTER,
    UPDATE_CHARACTER
};

#endif
