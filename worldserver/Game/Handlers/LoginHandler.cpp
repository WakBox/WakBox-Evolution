#include "Cryptography/CryptographyMgr.h"
#include "Server/WorldSession.h"
#include "Utils/Util.h"
#include "Proto/item.pb.h"
#include "Proto/equipment.pb.h"

void WorldSession::HandleClientVersion(WorldPacket& packet)
{
    quint8 version, change;
    quint16 revision;
    QString build;

    packet >> version;
    packet >> revision;
    packet >> change;
    build =  packet.ReadString();

    qDebug() << "BUILD: " << build;

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

    WorldPacket data(SMSG_CLIENT_AUTH_RESULT);

    if (!result.first())
    {
        data << (quint8) LOGIN_RESULT_ERROR_INVALID_LOGIN;
        SendPacket(data);

        return;
    }

    m_accountInfos.id               = result.value("account_id").toULongLong();
    m_accountInfos.username         = result.value("username").toString();
    m_accountInfos.pseudo           = result.value("pseudo").toString();
    m_accountInfos.gmLevel          = result.value("gm_level").toUInt();
    m_accountInfos.subscriptionTime = result.value("subscription_time").toUInt();

    data << (quint8) LOGIN_RESULT_SUCCESS;

    // if ban (=> ban check per realm?)
    // int banDuration in minutes

    data.StartBlock<quint16>();
    {
        // block number
        data << quint8(1);
        {
            data << quint8(0);      // block id
            data << quint32(6);     // block start

            data << quint8(0);      // block id

            data << quint64(result.value("account_id").toULongLong());
            data << quint32(101); // m_subscriptionLevel
            data << quint32(0); // antiAddictionLevel
            data << quint8(0); // m_additionalSlot
            data << quint64(m_accountInfos.subscriptionTime);

            // Hero subscription (hero system?)
            data << quint32(1); // m_heroSubscription count
                data << quint32(0); // unkInt
                data << quint64(0); // unkLong (heroId?)

            // Admin rights => TODO
            for (quint8 i = 1; i <= MAX_ADMIN_RIGHT + 6; ++i)
                data << quint32(0);

            data.WriteString(m_accountInfos.pseudo);

            data << (quint32) COMMUNITY_FR; // m_accountCommunity => TODO Community in accounts table

            // Account data (flags) TODO
            data << quint16(0); // flagCount
        }
    }
    data.EndBlock<quint16>();

    SendPacket(data);

    SendWorldSelectResult(true);

    // Send SMSG_FREE_COMPANION_BREED_ID - Opcode 2078
    WorldPacket data2(SMSG_FREE_COMPANION_BREED_ID);
    data2 << quint16(3075);
    SendPacket(data2);

    SendClientCalendarSync();
    SendSystemConfiguration();
    SendAdditionalSlotsUpdate();

    SendCompanionList();

    // Send ProtoMergedItems from item.proto
    WakfuProto::ProtoMergedItems protoMergedItems;

    WakfuProto::ProtoItem* item1 = protoMergedItems.add_items();
    WakfuProto::ProtoGems* gems1 = new WakfuProto::ProtoGems();

    item1->set_uniqueid(27407476768899124);
    item1->set_refid(14740);
    item1->set_qty(1);

    WakfuProto::ProtoGems_ProtoGem* gem1 = gems1->add_gems();
    gem1->set_position(0);
    gem1->set_refid(0);

    item1->set_allocated_gems(gems1);

    WakfuProto::ProtoItem* item2 = protoMergedItems.add_items();
    item2->set_uniqueid(27407476768899207);
    item2->set_refid(14743);
    item2->set_qty(1);

    WakfuProto::ProtoItem* item3 = protoMergedItems.add_items();
    item3->set_uniqueid(27407476752122374);
    item3->set_refid(14745);
    item3->set_qty(1);

    WakfuProto::ProtoItem* item4 = protoMergedItems.add_items();
    item4->set_uniqueid(27407476752122182);
    item4->set_refid(14741);
    item4->set_qty(1);

    WakfuProto::ProtoItem* item5 = protoMergedItems.add_items();
    item5->set_uniqueid(27407476785676493);
    item5->set_refid(14744);
    item5->set_qty(1);

    WakfuProto::ProtoItem* item6 = protoMergedItems.add_items();
    item6->set_uniqueid(27407476752122184);
    item6->set_refid(14742);
    item6->set_qty(1);

    WorldPacket data3(5256);
    QByteArray protoItemsBin;
    protoItemsBin.resize(protoMergedItems.ByteSize());
    protoMergedItems.SerializeToArray(protoItemsBin.data(), protoItemsBin.size());

    data3.StartBlock<quint32>();
    {
        data3.WriteRawBytes(protoItemsBin);
    }
    data3.EndBlock<quint32>();

    SendPacket(data3);

    // Send ProtoEquipmentAccount from equipment.proto
    WakfuProto::ProtoEquipmentAccount protoEquipmentAccount;
    WakfuProto::ProtoEquipmentSet* protoEquipmentSet = protoEquipmentAccount.add_sets();
    WakfuProto::ProtoEquipmentSheet* equipmentSheets = protoEquipmentSet->add_sheets();

    std::string emptyString = "";
    equipmentSheets->set_index(0);
    equipmentSheets->set_name(emptyString);
    equipmentSheets->set_level(-1);

    protoEquipmentSet->set_characterid(4299641297);

    WorldPacket data4(5255);
    QByteArray protoEquipmentSetBin;
    protoEquipmentSetBin.resize(protoEquipmentAccount.ByteSize());
    protoEquipmentAccount.SerializeToArray(protoEquipmentSetBin.data(), protoEquipmentSetBin.size());

    data4.StartBlock<quint32>();
    {
        data4.WriteRawBytes(protoEquipmentSetBin);
    }
    data4.EndBlock<quint32>();

    SendPacket(data4);

    // Characters list
    SendCharactersList();
}

// TODO ! An other token for reconnect????
void WorldSession::HandleAuthTokenRequest(WorldPacket& packet)
{
    quint64 address;
    quint16 languageLength;

    packet >> address;
    packet >> languageLength;
    QString language = packet.ReadString(languageLength);

    // Hardcoded token for now
    QString token = "74aed5af0c8551977d418cee34fa394bfd398565ba7b018d74c59999449ca";
    qDebug() << "Received token : " << token;

    WorldPacket data(MSG_AUTH_TOKEN);
    data.WriteString(token, STRING_SIZE_4);
    SendPacket(data);
}
