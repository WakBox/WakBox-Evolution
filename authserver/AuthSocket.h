#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Define.h"
#include "Databases/Database.h"
#include "Network/SocketHandler.h"

enum LoginResult
{
    LOGIN_RESULT_SUCCESS                = 0,
    LOGIN_RESULT_INVALID_LOGIN          = 2,
    LOGIN_RESULT_ALREADY_CONNECTED      = 3,
    LOGIN_RESULT_SAVE_IN_PROGRESSS      = 4,
    LOGIN_RESULT_ACCOUNT_BANNED         = 5
    // etc.
};

class AuthSocket : public SocketHandler
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    ~AuthSocket();

    virtual void ProcessPacket();
    void HandlePacket(quint16 opcode, WorldPacket& packet);

    void SendRSAPacket();
    void SendLoginResultPacket(QString account, QString password);

public slots:
    virtual void OnClose();

private:
};

#endif // AUTHSOCKET_H
