#include "Cryptography/CryptographyMgr.h"
#include "Server/WorldSession.h"

void WorldSession::HandleClientVersion(WorldPacket& packet)
{
    quint8 version, change;
    quint16 revision;
    QString build;

    packet >> version;
    packet >> revision;
    packet >> change;
    build =  packet.ReadString();

    QString clientVersion = QString(QString::number(version) + "." + QString::number(revision) + "." + QString::number(change));
    SendClientVersionResult(clientVersion, sAuthConfig->GetString("AcceptClientVersion"));
}

void WorldSession::SendClientVersionResult(QString clientVersion, QString expectedVersion)
{
    QStringList version = expectedVersion.split(".");

    WorldPacket data(SMSG_CLIENT_VERSION_RESULT);
    data << (quint8)(clientVersion == expectedVersion);
    data << (quint8)version.at(0).toUShort();
    data << (quint16)version.at(1).toUShort();
    data << (quint8)version.at(2).toUShort();
    data.WriteString("-1");
    SendPacket(data);
}

void WorldSession::HandlePublicKeyRequest(WorldPacket& /*packet*/)
{
    QByteArray publicKey = sCryptographyMgr->GetPublicKey();

    WorldPacket data(SMSG_PUBLIC_KEY_RESULT);
    data << quint64(0x8000000000000000); // Salt
    data.WriteRawBytes(publicKey);
    SendPacket(data);
}

void WorldSession::HandleClientAuthToken(WorldPacket& packet)
{
    quint32 tokenLength;
    packet >> tokenLength;

    QString token = packet.ReadString((quint8) tokenLength);
    QSqlQuery result = sAuthDatabase->Query(SELECT_ACCOUNT_BY_TOKEN, QVariantList() << token);

    if (!result.first())
    {
        SendWorldSelectResult(false);
        return;
    }

    SendWorldSelectResult(true);

    // Send SMSG_FREE_COMPANION_BREED_ID

    SendClientCalendarSync();

    // Send SMSG_SYSTEM_CONFIGURATION
    // Send SMSG_ADDITIONAL_CHARACTER_SLOTS_UPDATE
    // byte m_additionalSlots = 0

    SendCharactersList();
}
