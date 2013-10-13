#include "AuthServer.h"

template<> AuthServer*  Singleton<AuthServer>::m_instance = 0;

AuthServer::AuthServer()
{
    m_server = new QTcpServer(this);
    m_sockets.clear();
}

AuthServer::~AuthServer()
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping AuthServer...");

    ConfigMgr::Delete();
    Log::Delete();
    Database::Delete();

    SocketList::Iterator itr, next;
    for (itr = m_sockets.begin(); itr != m_sockets.end(); itr = next)
    {
        next = itr;
        ++next;

        delete (*itr);
        m_sockets.erase(itr);
    }

    m_server->close();
    delete m_server;
}

bool AuthServer::Initialize()
{
    if (!ConfigMgr::Instance()->LoadAuthConfig("authserver.conf"))
        return false;

    Log::Instance()->Init(ConfigMgr::Auth()->GetUShort("LogConsoleLevel"), ConfigMgr::Auth()->GetUShort("LogFileLevel"), ConfigMgr::Auth()->GetQString("LogFile"));
    Log::Write(LOG_TYPE_NORMAL, "Starting AuthServer...");

    //if (!Database::Instance()->OpenAuthDatabase())
    //    return close();

    if(!Start(QHostAddress::LocalHost, quint16(ConfigMgr::Auth()->GetInt("AuthServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, m_server->errorString().toLatin1().data());
        return false;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %i : waiting for connections", ConfigMgr::Auth()->GetInt("AuthServerPort"));

    // A mettre ailleurs
    OpcodeTable::Load();

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
    AuthSocket* newSockObject = new AuthSocket(socket);

    m_sockets.push_back(newSockObject);
}

void AuthServer::RemoveSocket(AuthSocket* socket)
{
    m_sockets.removeOne(socket);
}
