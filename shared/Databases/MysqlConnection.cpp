#include "MysqlConnection.h"
#include "Logs/Log.h"

MysqlConnection::MysqlConnection(ConnectionInfo& connectionInfo)
{
    m_connectionInfo = connectionInfo;

    m_db = QSqlDatabase::addDatabase("QMYSQL", m_connectionInfo.database);
    m_db.setHostName(m_connectionInfo.host);
    m_db.setPort(m_connectionInfo.port);
    m_db.setDatabaseName(m_connectionInfo.database);
    m_db.setUserName(m_connectionInfo.username);
    m_db.setPassword(m_connectionInfo.password);

    m_db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
}

MysqlConnection::~MysqlConnection()
{
    Close();
}

bool MysqlConnection::Open(bool loadQueries)
{
    if(!m_db.open())
    {
        Log::Write(LOG_TYPE_NORMAL, "Error when trying to connect to database %s : %s", m_connectionInfo.database.toLatin1().data(), m_db.lastError().text().toLatin1().data());
        return false;
    }

    if (loadQueries)
        LoadQueries();

    Log::Write(LOG_TYPE_NORMAL, "Database connection accomplished on %s", m_connectionInfo.database.toLatin1().data());
    return true;
}

bool MysqlConnection::Reconnect()
{
    Log::Write(LOG_TYPE_NORMAL, "MySQL connection lost. Trying to reconnect...");
    Close();

    if (Open(false))
        return true;

    return false;
}

void MysqlConnection::Close()
{
    if (m_db.isOpen())
    {
        m_db.close();
        Log::Write(LOG_TYPE_NORMAL, "Closing database connection on %s", m_connectionInfo.database.toLatin1().data());
    }
}

QSqlQuery MysqlConnection::Query(QString sqlQuery, QVariantList args)
{
    if(sqlQuery.isEmpty() || !m_db.isOpen())
        return QSqlQuery();

    QSqlQuery query = QSqlQuery(m_db);
    query.prepare(sqlQuery);

    while (!args.isEmpty())
        query.addBindValue(args.takeFirst());

    if(!query.exec())
    {
        Log::Write(LOG_TYPE_NORMAL, "SQL error with %s", sqlQuery.toLatin1().data());
        Log::Write(LOG_TYPE_NORMAL, "[Error %u] %s", query.lastError().number(), query.lastError().text().toLatin1().data());

        if (query.lastError().number() == 2013 || query.lastError().number() == 2003)
            Log::Write(LOG_TYPE_NORMAL, "MySQL connection lost.");
    }

    return query;
}

QSqlQuery MysqlConnection::Query(quint16 sqlQueryId, QVariantList args)
{
    return Query(GetSqlQuery(sqlQueryId), args);
}
