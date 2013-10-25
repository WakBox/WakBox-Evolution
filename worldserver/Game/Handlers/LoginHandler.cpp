#include "Server/WorldSession.h"
#include "Configuration/ConfigMgr.h"
#include "Cryptography/Cryptography.h"
#include "Utils/Util.h"

void WorldSession::HandleClientVersion(WorldPacket &packet)
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

void WorldSession::HandleClientAuthentication(WorldPacket &packet)
{
    QByteArray buffer;
    buffer.resize(packet.GetPacket().length());
    packet.ReadRawBytes(buffer.data(), buffer.size());

    WorldPacket decrypted(0, Cryptography::Instance()->Decrypt(buffer));

    quint64 rsaVerification;
    decrypted >> rsaVerification;

    QString account = decrypted.ReadString();
    QString password = decrypted.ReadString();

    // Send login result

    QSqlQuery result = Database::Auth()->Query(SELECT_ACCOUNT_BY_USERNAME, QVariantList() << account);
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    LoginResult loginResult = LOGIN_RESULT_INVALID_LOGIN;

    if (!result.first())
    {
        data << (quint8)loginResult;
        SendPacket(data);
        return;
    }

    QSqlRecord fields = result.record();
    QString hashPassword = result.value(fields.indexOf("hash_password")).toString();

    if (Utils::HashPassword(account, password) == hashPassword)
    {
        loginResult = LOGIN_RESULT_SUCCESS;
    }

    data << (quint8)loginResult;

    if (loginResult != LOGIN_RESULT_SUCCESS)
    {
        if (loginResult == LOGIN_RESULT_ACCOUNT_BANNED)
        {
            // data << quint32(banDelay);
        }

        return SendPacket(data);
    }

    data.StartBlock<quint16>();
    {
        data << quint8(1);
        data << quint8(0);
        data << quint32(6);
        data << quint8(0);
        data << quint64(result.value(fields.indexOf("account_id")).toULongLong());
        data << quint8(0);
        data << quint64(0); // Subscribe
        data << quint32(0); // isAdmin ? 1 : 0
        data.WriteString(account);
        data.WriteString("??");
        data << quint16(00);
    }
    data.EndBlock<quint16>();

    SendPacket(data);

    // Send World list
    SendWorldList();
}

void WorldSession::SendWorldList()
{
    WorldPacket data(SMSG_WORLD_LIST);
    data << quint8(1); // World count

    // La structure doit être fausse
    data.StartBlock<quint8>();
    {
        data << quint8(3);
        data << quint8(0);
        data << quint32(16);
        data << quint8(1);
        data << quint32(24);
        data << quint8(2);
        data << quint32(36);

        data << quint8(0);
        data << quint32(1606); // World Id
        data.WriteString("1W");

        data << quint8(1);
        data.WriteString("Wakboxx"); // Name - 7char, if other change the server status wtf ?
        data.WriteString("fr"); // Language

        data << quint8(2);
        data << quint8(1); // Status (0 = offline, 1 = online)
        data << quint8(0);
        data << quint8(0); // Population
    }
    data.EndBlock<quint8>();
    SendPacket(data);
}
