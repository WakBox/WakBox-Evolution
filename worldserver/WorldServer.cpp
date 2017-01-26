#include "WorldServer.h"
#include "Chat/Chat.h"
#include "Cryptography/CryptographyMgr.h"
#include "Game/Server/WorldSession.h"
#include "Game/World/World.h"
#include "Game/World/WorldRunnable.h"

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
    CryptographyMgr::Delete();
    Database::Delete();
    Log::Delete();
    Chat::Delete();

    m_server->deleteLater();
    m_server = NULL;
}

bool WorldServer::Initialize()
{
    if (!sConfigMgr->LoadAuthConfig("authserver.conf"))
        return false;

    if (!sConfigMgr->LoadWorldConfig("worldserver.conf"))
        return false;

    Log::Instance()->Initialize(sWorldConfig->GetUShort("LogConsoleLevel"), sWorldConfig->GetUShort("LogFileLevel"), sWorldConfig->GetString("LogFile"));
    Log::Write(LOG_TYPE_NORMAL, "Starting WorldServer...");

    if (!sDatabase->OpenAuthDatabase(sAuthConfig->GetString("AuthDatabase")))
        return false;

    if (!sDatabase->OpenCharDatabase(sWorldConfig->GetString("CharDatabase")))
        return false;

    if (!sDatabase->OpenWorldDatabase(sWorldConfig->GetString("WorldDatabase")))
        return false;

    OpcodeTable::Load();

    if (!sCryptographyMgr->Initialize())
        return false;

    if (!World::Instance()->Initialize())
    {
        Log::Write(LOG_TYPE_NORMAL, "World initialization failed. Exiting.");
        return false;
    }

    if(!Start(QHostAddress::LocalHost, quint16(sWorldConfig->GetInt("WorldServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, m_server->errorString().toLatin1().data());
        return false;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "Worldserver started on port %i : waiting for connections", sWorldConfig->GetInt("WorldServerPort"));

    Chat::Instance();
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
