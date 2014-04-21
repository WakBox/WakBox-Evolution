#include "Server/WorldSession.h"
#include "Configuration/ConfigMgr.h"
#include "Cryptography/Cryptography.h"
#include "Utils/Util.h"

void WorldSession::HandleClientVersion(WorldPacket& packet)
{
    quint8 version, change;
    quint16 revision;

    packet >> version;
    packet >> revision;
    packet >> change;

    QString clientVersion = QString(QString::number(version) + "." + QString::number(revision) + "." + QString::number(change));

    if (clientVersion != ConfigMgr::Instance()->GetWorldConfig()->GetQString("AcceptClientVersion"))
    {
        QStringList version = ConfigMgr::Instance()->GetWorldConfig()->GetQString("AcceptClientVersion").split(".");
        WorldPacket data(SMSG_BAD_CLIENT_VERSION);
        data << (quint8)version.at(0).toUShort();
        data << (quint16)version.at(1).toUShort();
        data << (quint8)version.at(2).toUShort();
        data.WriteString("-1");
        SendPacket(data);
    }
    else
    {
        QByteArray publicKey = Cryptography::Instance()->GetPublicKey();

        WorldPacket data(SMSG_RSA_PUBLIC_KEY);
        data << quint64(0x8000000000000000);
        data.WriteRawBytes(publicKey.data(), publicKey.length());
        SendPacket(data);
    }
}

void WorldSession::HandleClientAuthentication(WorldPacket& packet)
{
    quint32 bufferSize;
    packet >> bufferSize;

    QByteArray buffer;
    buffer.resize(bufferSize);
    packet.ReadRawBytes(buffer.data(), buffer.size());

    WorldPacket decrypted(0, Cryptography::Instance()->Decrypt(buffer));

    quint64 rsaVerification;
    decrypted >> rsaVerification;

    QString account = decrypted.ReadString();
    QString password = decrypted.ReadString();

    QSqlQuery result = Database::Auth()->Query(SELECT_ACCOUNT_BY_USERNAME, QVariantList() << account);

    if (!result.first())
    {
        SendLoginErrorResult(LOGIN_RESULT_INVALID_LOGIN);
        return;
    }

    QSqlRecord fields = result.record();
    QString hashPassword = result.value(fields.indexOf("hash_password")).toString();

    if (Utils::HashPassword(account, password) != hashPassword)
    {
        SendLoginErrorResult(LOGIN_RESULT_INVALID_LOGIN);
        return;
    }

    m_accountInfos.id = result.value(fields.indexOf("account_id")).toULongLong();
    m_accountInfos.username = result.value(fields.indexOf("username")).toString();
    m_accountInfos.pseudo = result.value(fields.indexOf("pseudo")).toString();
    m_accountInfos.gmLevel = (quint8)result.value(fields.indexOf("username")).toUInt();
    m_accountInfos.subscriptionTime = result.value(fields.indexOf("subscription_time")).toUInt();

    // Send opcode 2 (connection retry ticket, not implemented)
    WorldPacket data2(SMSG_CONNECTION_RETRY_TICKET);
    SendPacket(data2);

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(LOGIN_RESULT_SUCCESS);

    data.StartBlock<quint16>();
    {
        data << quint8(1);
        {
            data << quint8(0);
            data << quint32(6);
            data << quint8(0);

            data << quint64(result.value(fields.indexOf("account_id")).toULongLong());
            data << quint32(1); // m_subscriptionLevel
            data << quint32(0); // antiAddictionLevel
            data << quint64(m_accountInfos.subscriptionTime);

            // Admin rights ?
            for (quint8 i = 0; i <= 75; ++i)
                data << quint32(0);

            data.WriteString(m_accountInfos.pseudo);

            data << quint32(0); // m_accountCommunity ID, see Wl.java for IDs
            data << quint16(0); // size of hdv, see bOE.java something with m_accountCommunity and check TS.java
        }
    }
    data.EndBlock<quint16>();

    SendPacket(data);
    SendWorldSelectResult();
}

void WorldSession::SendLoginErrorResult(LoginResult result)
{
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(result);
    SendPacket(data);
}

void WorldSession::HandleClientDisconnect(WorldPacket& /*packet*/)
{
    Character* character = GetCharacter();
    if (!character)
        return;

    //qDebug() << "Character " << character->GetName() << " saved to DB";
    //character->SaveToDB();
}
