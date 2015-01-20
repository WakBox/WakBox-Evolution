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
    SMSG_CLIENT_AUTH_RESULT                     = 1027,
    SMSG_PUBLIC_KEY                             = 1034,
    SMSG_REALMS_LIST                            = 1036,
    SMSG_AUTH_TOKEN_RESULT                      = 1212,
};

enum OpcodeStatus
{
    STATUS_UNHANDLED = 0,
    STATUS_ALWAYS,
    STATUS_NEVER,
    STATUS_AUTHED
};

enum LoginResult
{
    LOGIN_RESULT_SUCCESS                        = 0,
    LOGIN_RESULT_ERROR_INVALID_LOGIN            = 2,
    LOGIN_RESULT_ALREADY_CONNECTED              = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS              = 4,
    LOGIN_RESULT_ERROR_BANNED                   = 5,
    LOGIN_RESULT_ERROR_INTERNAL                 = 7,
    LOGIN_RESULT_ACCOUNT_LOCKED                 = 9,
    LOGIN_RESULT_SERVER_DOWN                    = 10,
    LOGIN_RESULT_TOO_MANY_CONNECTIONS           = 11,
    LOGIN_RESULT_ERROR_INVALID_PARTNER          = 12,
    LOGIN_RESULT_NICKNAME_NOT_SET               = 13,
    LOGIN_RESULT_NICKNAME_INVALID_CONTENT       = 14,
    LOGIN_RESULT_NICKNAME_DUPLICATE             = 15,
    LOGIN_RESULT_NICKNAME_TOO_LONG              = 16,
    LOGIN_RESULT_NICKNAME_TOO_SHORT             = 17,
    LOGIN_RESULT_NICKNAME_EQUALS_LOGIN          = 18,
    LOGIN_RESULT_NICKNAME_ERROR                 = 19,
    LOGIN_RESULT_ERROR_ACCOUNT_INVALID_EMAIL    = 20,
    LOGIN_RESULT_ACCOUNT_UNDER_MODERATION       = 21,
    LOGIN_RESULT_ERROR_OTP_AUTH_FAILED          = 22,
    LOGIN_RESULT_ERROR_EXTERNAL_ACCOUNT_LINKED  = 23,
    LOGIN_RESULT_ERROR_EXTERNAL_NO_ACCOUNT      = 24,
    LOGIN_RESULT_ERROR_FORBIDDEN_COMMUNITY      = 25,
    LOGIN_RESULT_SECURITY_CARD                  = 26,
    LOGIN_RESULT_CLOSED_BETA                    = 127
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
    OpcodeStatus status;
    void (AuthSession::*handler)(WorldPacket& packet);
};

typedef void(AuthSession::*authHandler)(WorldPacket& packet);
typedef QMap<AuthOpcodes, AuthHandler> AuthHandlerMap;

class AuthTable
{
public:
    static void InitHandlers();

    static void AddOpcodeHandler(quint16 opcode, char const* name, OpcodeStatus status, authHandler handler)
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
