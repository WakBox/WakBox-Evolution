#include "worldserver.h"
#include "Game/World/World.h"
#include "Cryptography/Cryptography.h"

template<> WorldServer*  Singleton<WorldServer>::m_instance = 0;

WorldServer::WorldServer()
{
    m_server = new QTcpServer();
}

WorldServer::~WorldServer()
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping Worldserver...");

    World::Delete();
    ConfigMgr::Delete();
    Cryptography::Delete();
    Database::Delete();
    Log::Delete();

    m_server->close();
    delete m_server;
}

bool WorldServer::Initialize()
{
    if (!ConfigMgr::Instance()->LoadWorldConfig("worldserver.conf"))
        return false;

    Log::Instance()->Initialize(ConfigMgr::World()->GetUShort("LogConsoleLevel"), ConfigMgr::World()->GetUShort("LogFileLevel"), ConfigMgr::World()->GetQString("LogFile"));
    Log::Write(LOG_TYPE_NORMAL, "Starting WorldServer...");

    if (!Database::Instance()->OpenAuthDatabase())
        return false;

    if (!Database::Instance()->OpenCharDatabase())
        return false;

    if (!Database::Instance()->OpenWorldDatabase())
        return false;

    OpcodeTable::Load();

    if (!Cryptography::Instance()->Initialize())
        return false;

    if (!World::Instance()->Initialize())
    {
        Log::Write(LOG_TYPE_NORMAL, "World initialization failed. Exiting.");
        return false;
    }

    if(!WorldServer::Instance()->Start(QHostAddress::LocalHost, quint16(ConfigMgr::World()->GetInt("WorldServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, m_server->errorString().toLatin1().data());
        return false;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "Worldserver started on port %i : waiting for connections", ConfigMgr::World()->GetInt("WorldServerPort"));

    return true;
}

bool WorldServer::Start(QHostAddress address, quint16 port)
{
    if(!m_server->listen(address, port))
        return false;

    connect(m_server, SIGNAL(newConnection()), this, SLOT(OnConnect()));
    return true;
}

void WorldServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    WorldSession* session = new WorldSession(socket);

    World::Instance()->AddSession(session);
}
