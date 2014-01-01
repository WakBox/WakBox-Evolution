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
    QByteArray buffer;
    buffer.resize(packet.GetPacket().length());
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

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << LOGIN_RESULT_SUCCESS;

    data.StartBlock<quint16>();
    {
        data << quint8(1);
        {
            data << quint8(0);
            data << quint32(6);
            data << quint8(0);

            data << quint64(result.value(fields.indexOf("account_id")).toULongLong());
            data << quint8(0);
            data << quint64(0); // Subscribe
            data << quint32(0); // isAdmin ? 1 : 0

            data.WriteString(account);
            data.WriteString("??");

            data << quint16(0);
        }
    }
    data.EndBlock<quint16>();

    SendPacket(data);
    SendWorldList();
}

void WorldSession::SendLoginErrorResult(LoginResult result)
{
    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);
    data << quint8(result);
    SendPacket(data);
}

void WorldSession::SendWorldList()
{
    QSqlQuery result = Database::Auth()->Query(SELECT_WORLD_ID, QVariantList() << ConfigMgr::Instance()->GetWorldConfig()->GetUShort("WorldId"));

    WorldPacket data(SMSG_WORLD_LIST);
    data << quint8(result.size());

    if (result.first())
    {
        QSqlRecord fields = result.record();

        data.StartBlock<quint8>();
        {
            quint8 blockCount = 3;
            data << blockCount;

            for (quint8 i = 0; i < blockCount; ++i)
            {
                data << i;
                data.StartBlock<quint32>(i + 1);
            }

            // Block 0
            {
                data.EndBlockAbsolute<quint32>(1, -6);
                data << quint8(0);

                data << quint32(result.value(fields.indexOf("world_id")).toUInt());
                data.WriteString("1W");
            }

            // Block 1
            {
                data.EndBlockAbsolute<quint32>(2, -6);
                data << quint8(1);

                data.WriteString(result.value(fields.indexOf("name")).toString());
                data.WriteString(result.value(fields.indexOf("language")).toString());
            }

            // Block 2
            {
                data.EndBlockAbsolute<quint32>(3, -6);
                data << quint8(2);

                // 0 = offline, 1 = online
                data << quint8(result.value(fields.indexOf("status")).toUInt());
                // 0 = not full, 1 = full
                data << quint8(0);
                data << quint8(result.value(fields.indexOf("population")).toUInt());
            }
        }
        data.EndBlock<quint8>();
    }

    SendPacket(data);
}
