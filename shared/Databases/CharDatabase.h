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
};

#endif
