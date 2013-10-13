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
        qDebug() << m_db.lastError();
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
    m_db.close();
    Log::Write(LOG_TYPE_NORMAL, "Closing database connection on %s", m_connectionInfo.database.toLatin1().data());
}

QSqlQuery MysqlConnection::Query(QString sqlQuery)
{
    if(sqlQuery.isEmpty() || !m_db.isOpen())
        return QSqlQuery();

    QSqlQuery req = QSqlQuery(m_db);

    if(!req.exec(sqlQuery))
    {
        Log::Write(LOG_TYPE_NORMAL, "SQL error with %s", sqlQuery.toLatin1().data());
        Log::Write(LOG_TYPE_NORMAL, "[Error %u] %s", req.lastError().number(), req.lastError().text().toLatin1().data());

        if (req.lastError().number() == 2013 || req.lastError().number() == 2003)
        {
            if (Reconnect())
                Query(sqlQuery);
            else
                Log::Write(LOG_TYPE_NORMAL, "Reconnect failed : MySQL connection lost.");
        }
    }

    return req;
}

QSqlQuery MysqlConnection::PQuery(QString sqlQuery, ...)
{
    if(sqlQuery.isEmpty() || !m_db.isOpen())
        return QSqlQuery();

    va_list ap;
    va_start(ap, sqlQuery);
    QString query;
    query.vsprintf(sqlQuery.toLatin1().data(), ap);

    return Query(query);
}

QSqlQuery MysqlConnection::Query(quint16 sqlQueryId)
{
    return Query(GetSqlQuery(sqlQueryId));
}

QSqlQuery MysqlConnection::PQuery(quint16 sqlQueryId, ...)
{
    QString sqlQuery = GetSqlQuery(sqlQueryId);
    va_list ap;
    va_start(ap, sqlQuery);
    QString query;
    query.vsprintf(sqlQuery.toLatin1().data(), ap);

    return Query(query);
}
