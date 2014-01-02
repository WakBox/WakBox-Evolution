#include "Server/WorldSession.h"
#include "Entities/ObjectMgr.h"

void WorldSession::SendCharactersList()
{
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTERS_BY_ACCOUNT_ID, QVariantList() << GetAccountInfos().id);

    WorldPacket data(SMSG_CHAR_LIST);
    data << quint8(result.size());

    while (result.next())
    {
        QSqlRecord fields = result.record();

        data.StartBlock<quint16>();
        {
            // Block type
            data << quint8(4);
            data << quint64(result.value(fields.indexOf("guid")).toULongLong());

            data << quint8(0); // idType ?
            data << quint64(result.value(fields.indexOf("account_id")).toULongLong());

            data.WriteString(result.value(fields.indexOf("name")).toString(), true);
            data << quint16(result.value(fields.indexOf("breed")).toUInt());

            data << quint8(result.value(fields.indexOf("gender")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color")).toUInt());
            data << quint8(result.value(fields.indexOf("pupil_color")).toUInt());
            data << quint8(result.value(fields.indexOf("skin_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("hair_color_factor")).toUInt());
            data << quint8(result.value(fields.indexOf("cloth")).toUInt());
            data << quint8(result.value(fields.indexOf("face")).toUInt());
            data << qint16(result.value(fields.indexOf("title")).toUInt());

            //Stuff
            data << quint16(0); // Size
            /*{
                buffer.writeShort(22); //position
                buffer.writeLong(28243842327118258L); //uid
                buffer.writeInt(12237); //refid
                buffer.writeShort(1); //amt
                buffer.writeByte(0); //hasTimestamp
                buffer.writeByte(1); { //haspet
                    buffer.writeInt(5); //defId
                    buffer.writeBigString("");
                    buffer.writeInt(14152);
                    buffer.writeInt(0); //equippedRefItemId
                    buffer.writeInt(20); //hp
                    buffer.writeInt(10); //xp
                    buffer.writeByte(5); //fightCounter
                    buffer.writeLong(1351188368000L);
                    buffer.writeLong(1351188368000L);
                    buffer.writeLong(1351188368000L);
                    buffer.writeInt(0); //sleeprefitemid
                    buffer.writeLong(0); //sleepdate
                }
                buffer.writeByte(0); //hasxp
                buffer.writeByte(0); //hasgems
            }
            */

            data << quint8(0); //no creation data

            // XP
            data << quint64(result.value(fields.indexOf("xp")).toULongLong());
            data << quint16(0); // Free points

            data << quint16(0);
            /*int[] points = new int[] {40, 37, 39, 36, 41, 38};
            buffer.writeShort(6);
            for (int i=0; i<points.length; i++) {
                buffer.writeByte(points[i]);
                buffer.writeShort(0);
            }
            */

            data << quint16(0);
            /*buffer.writeShort(6); //characteristicBonusPointCount
            for (int i=0; i<points.length; i++) {
                buffer.writeByte(points[i]);
                buffer.writeShort(0);
            }
            */

            data << quint32(0); // Gauge

            data << quint32(1); //Nation
        }
        data.EndBlock<quint16>();
    }

    SendPacket(data);
}

void WorldSession::HandleLeaveCharSelect(WorldPacket& /*packet*/)
{
    WorldPacket data(SMSG_LEAVE_CHAR_SELECT);
    SendPacket(data);
}

void WorldSession::HandleCharDelete(WorldPacket& packet)
{
    quint64 guid;
    packet >> guid;

    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_BY_GUID, QVariantList() << guid);
    quint8 success = 0;

    if (result.first())
    {
        if (result.value(result.record().indexOf("account_id")) == GetAccountInfos().id)
        {
            Database::Char()->Query(DELETE_CHARACTER_BY_GUID, QVariantList() << guid);
            success = 1;
        }
    }

    if (!success)
    {
        SendCharDeleteResult(guid, success);
        return;
    }

    SendSecretAnswerRequest();

    // - this is TMP
    WorldPacket data(SMSG_CHAR_DELETE_CONFIRM);
    data << success;
    SendPacket(data);

    SendCharDeleteResult(guid, success);
}

void WorldSession::SendCharDeleteResult(quint64 guid, quint8 success)
{
    WorldPacket data(SMSG_CHAR_DELETE);
    data << guid;
    data << success;
    SendPacket(data);
}

void WorldSession::SendSecretAnswerRequest()
{
    // TODO
}

void WorldSession::HandleSecretAnswerResponse(WorldPacket& packet)
{
    //Database::Char()->Query(DELETE_CHARACTER, QVariantList() << GetAccountInfos().id << guid);

    /* Si tout est OK
    WorldPacket data(SMSG_CHAR_DELETE_CONFIRM);
    data << success;
    SendPacket(data);

    SendCharDeleteResult(guid, success);
    */
}

void WorldSession::HandleCharCreate(WorldPacket& packet)
{
    quint64 unk;
    quint8 gender, skinColor, hairColor, pupilColor;
    quint8 skinColorFactor, hairColorFactor, cloth, face;
    quint16 breed;
    QString name;

    packet >> unk;

    packet >> gender >> skinColor >> hairColor >> pupilColor;
    packet >> skinColorFactor >> hairColorFactor >> cloth >> face;

    packet >> breed;

    name = packet.ReadString();

    WorldPacket data(SMSG_CHAR_CREATE);
    QSqlQuery result = Database::Char()->Query(SELECT_CHARACTER_BY_NAME, QVariantList() << name);

    if (!result.first())
    {
        // TODO
        // Check max char by account

        sCharacterCreateInfos charCreateInfos(name, breed, gender, skinColor, hairColor, pupilColor,
                                              skinColorFactor, hairColorFactor, cloth, face);

        QScopedPointer<Character> newChar(new Character(this));

        if(newChar->Create(ObjectMgr::Instance()->GenerateGuid(GUIDTYPE_CHARACTER), charCreateInfos))
        {
            newChar->SaveToDB(true);

            data << quint8(0);
            SendPacket(data);

            SendSelectCharacterResult(true);
            SendCharactersList();
            return;
        }
    }

    data << quint8(10);
    SendPacket(data);
}

void WorldSession::HandleCharSelect(WorldPacket& packet)
{
    quint64 guid;
    packet >> guid;

    // Check if characters isn't already loaded or in loading.
    /*
    if (PlayerLoading() || GetPlayer() != NULL)
    {
        TC_LOG_ERROR(LOG_FILTER_NETWORKIO, "Player tries to login again, AccountId = %d", GetAccountId());
        return;
    }

    m_playerLoading = true;
    */

    // Is this character owned by this account ?

    Character* character = new Character(this);
    if (!character->LoadFromDB(guid))
    {
        delete character;
        // m_playerLoading = false;
        return;
    }

    SendSelectCharacterResult(true);
    SendEnterWorld(character);

}

void WorldSession::SendSelectCharacterResult(bool result)
{
    WorldPacket data(SMSG_CHAR_SELECT);
    data << quint8((result) ? 0 : 1);
    SendPacket(data);
}

void WorldSession::SendEnterWorld(Character* character)
{
    WorldPacket data(SMSG_ENTER_WORLD);
    data << quint64(character->GetGuid());
    data.StartBlock<quint16>();
    {
        data << quint8(15);
        data << quint32(0); // Nation Id
        data << quint64(0); // Ranks
        data << quint64(0); // Jobs
        data << quint64(0); // Votedate
        data << quint8(0); // Government Opionion
        data << quint8(0); // IsCandidate (bool)

        data << quint16(0); // Guild info
    }
    data.EndBlock<quint16>();

    SendPacket(data);
}
