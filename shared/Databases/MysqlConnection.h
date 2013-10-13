#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <QtCore>
#include <QtSql>

struct ConnectionInfo
{
    ConnectionInfo() {}
    ConnectionInfo(QString connectionInfo)
    {
        QStringList infos = connectionInfo.split(':');

        host = infos.at(0);
        port = QString(infos.at(1)).toInt();
        username = infos.at(2);
        password = infos.at(3);
        database = infos.at(4);
    }

    QString host;
    int port;
    QString username;
    QString password;
    QString database;
};

typedef QMap<quint16, QString> QueriesMap;

class MysqlConnection
{
public:
    MysqlConnection(ConnectionInfo& connectionInfo);
    virtual ~MysqlConnection();

    virtual void LoadQueries() = 0;
    void LoadQuery(quint16 id, QString sql)
    {
        m_queries[id] = sql;
    }

    bool Open(bool loadQueries = true);
    bool Reconnect();
    void Close();

    QString GetSqlQuery(quint16 sqlQueryId)
    {
        QueriesMap::ConstIterator itr = m_queries.find(sqlQueryId);

        if(itr != m_queries.end())
            return m_queries[sqlQueryId];
        return QString();
    }

    QSqlQuery Query(QString sqlQuery);
    QSqlQuery PQuery(QString sqlQuery, ...);

    QSqlQuery Query(quint16 sqlQueryId);
    QSqlQuery PQuery(quint16 sqlQueryId, ...);

protected:
    QueriesMap m_queries;

private:
    ConnectionInfo m_connectionInfo;
    QSqlDatabase m_db;
};

#endif
