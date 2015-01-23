#ifndef AUTHSESSION_H
#define AUTHSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Define.h"
#include "Databases/Database.h"
#include "Network/SocketHandler.h"

enum AuthOpcodes
{
    // Client messages (CMSG)
    CMSG_CLIENT_DISCONNECT                      = 1,
    CMSG_CLIENT_VERSION                         = 7,
    CMSG_CLIENT_AUTH                            = 1026,
    CMSG_PUBLIC_KEY_REQUEST                     = 1033,
    CMSG_REALMS_REQUEST                         = 1035,
    CMSG_AUTH_TOKEN_REQUEST                     = 1211,

    // Server messages (SMSG)
    SMSG_CONNECTION_RETRY_TICKET                = 2,
    SMSG_CLIENT_VERSION_RESULT                  = 8,
    SMSG_CLIENT_IP                              = 110,
    SMSG_CLIENT_AUTH_RESULT                     = 1027,
    SMSG_PUBLIC_KEY                             = 1034,
    SMSG_REALMS_LIST                            = 1036,
    SMSG_AUTH_TOKEN_RESULT                      = 1212,
};

enum SessionStatus
{
    STATUS_UNHANDLED = 0,       // Opcode not handled
    STATUS_ALWAYS,              // Opcode always accepted
    STATUS_NEVER,               // Opcode not accepted from client (deprecated or server side only)
    STATUS_AUTHED               // Player authenticated
};

class AuthSession : public SocketHandler
{
    Q_OBJECT
public:

    AuthSession(QTcpSocket* socket);
    ~AuthSession();

    virtual void ProcessPacket();
    virtual void SendPacket(WorldPacket& data);

    // Default handlers
    void HandleServerSide(WorldPacket& /*packet*/) {}

    // CMSG Handlers
    void HandleClientDisconnect(WorldPacket& /*packet*/);
    void HandleClientVersion(WorldPacket& packet);
    void HandlePublicKeyRequest(WorldPacket& /*packet*/);
    void HandleClientAuthentication(WorldPacket& packet);
    void HandleRealmsRequest(WorldPacket& /*packet*/);
    void HandleAuthTokenRequest(WorldPacket& packet);

    void SendClientVersionResult(QString clientVersion, QString expectedVersion);
    void SendLoginErrorResult(LoginResult result);

public slots:
    virtual void OnClose();

private:
    bool m_logout;
    quint32 m_accountId;
    QString m_username;
};

struct AuthHandler
{
    QString name;
    SessionStatus status;
    void (AuthSession::*handler)(WorldPacket& packet);
};

typedef void(AuthSession::*authHandler)(WorldPacket& packet);
typedef QMap<AuthOpcodes, AuthHandler> AuthHandlerMap;

class AuthTable
{
public:
    static void InitHandlers();

    static void AddOpcodeHandler(quint16 opcode, char const* name, SessionStatus status, authHandler handler)
    {
        AuthHandler opcodeHandler;
        opcodeHandler.name = QString(name);
        opcodeHandler.status = status;
        opcodeHandler.handler = handler;

        authHandlers.insert((AuthOpcodes)opcode, opcodeHandler);
    }

    static bool Exists(quint16 id)
    {
        return authHandlers.contains((AuthOpcodes)id);
    }

    static AuthHandler Get(quint16 id)
    {
        return authHandlers.value((AuthOpcodes)id);
    }

private:
    static AuthHandlerMap authHandlers;
};

#endif // AUTHSESSION_H
