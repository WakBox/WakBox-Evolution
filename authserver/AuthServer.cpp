#include "AuthServer.h"
#include "Cryptography/CryptographyMgr.h"
#include "Databases/Database.h"
#include "Logs/Log.h"

template<> AuthServer*  Singleton<AuthServer>::m_instance = 0;

AuthServer::AuthServer()
{
    m_server = new QTcpServer(this);
}

AuthServer::~AuthServer()
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping AuthServer...");

    ConfigMgr::Delete();
    CryptographyMgr::Delete();
    Database::Delete();
    Log::Delete();

    SocketList::Iterator itr, next;
    for (itr = m_sockets.begin(); itr != m_sockets.end(); itr = next)
    {
        next = itr;
        ++next;

        delete (*itr);
        m_sockets.erase(itr);
    }

    m_server->deleteLater();
    m_server = NULL;
}

bool AuthServer::Initialize()
{
    if (!sConfigMgr->LoadAuthConfig("authserver.conf"))
        return false;

    Log::Instance()->Initialize(sAuthConfig->GetUShort("LogConsoleLevel"), sAuthConfig->GetUShort("LogFileLevel"), sAuthConfig->GetString("LogFile"));
    Log::Write(LOG_TYPE_NORMAL, "Starting AuthServer...");

    if (!sDatabase->OpenAuthDatabase(sAuthConfig->GetString("AuthDatabase")))
        return false;

    if (!sCryptographyMgr->Initialize())
        return false;

    AuthTable::InitHandlers();

    if(!Start(QHostAddress::LocalHost, quint16(sAuthConfig->GetInt("AuthServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, m_server->errorString().toLatin1().data());
        return false;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %i : waiting for connections", sAuthConfig->GetInt("AuthServerPort"));

    return true;
}

bool AuthServer::Start(QHostAddress address, quint16 port)
{
    if(!m_server->listen(address, port))
        return false;

    connect(m_server, SIGNAL(newConnection()), this, SLOT(OnConnect()));
    return true;
}

void AuthServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    AuthSession* session = new AuthSession(socket);

    m_sockets.push_back(session);
}

void AuthServer::RemoveSocket(AuthSession* socket)
{
    m_sockets.removeOne(socket);
}
