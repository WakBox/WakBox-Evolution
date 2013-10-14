#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include "Define.h"
#include "Databases/Database.h"
#include "Network/SocketHandler.h"

class AuthSocket : public SocketHandler
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    ~AuthSocket();

    virtual void ProcessPacket();
    void HandlePacket(quint16 opcode, WorldPacket& packet);

    void SendRSAPacket();
    void SendLoginResultPacket();

public slots:
    virtual void OnClose();

private:
    RSA* m_keyPair;
    X509* m_cert;
};

#endif // AUTHSOCKET_H
