#include "Server/WorldSession.h"

void WorldSession::HandleChatMessage(WorldPacket& packet)
{
    Character* character = GetCharacter();
    if (!character)
        return;

    QString message = packet.ReadString();
    qDebug() << "Chat message : " << message;

    // Send to all characters in range
    WorldPacket data(SMSG_CHAT_MESSAGE);
    data.WriteString(character->GetName());
    data << character->GetGuid();
    data.WriteString(message);
    // SendPacket(data); -> only for players in range TODO
}

void WorldSession::HandlePrivateMessage(WorldPacket& packet)
{
    QString toCharacterName = packet.ReadString();
    QString message = packet.ReadString();

    // Send to character but check aVi for SendPrivateMessageResult
    // Packet 3154
}

void WorldSession::HandleTradeMessage(WorldPacket& packet)
{
    QString message = packet.ReadString();
    qDebug() << "Trade message : " << message;
}

void WorldSession::HandleRecruitMessage(WorldPacket& /*packet*/)
{

}

void WorldSession::SendModerationRequest()
{
    WorldPacket data(SMSG_HAS_MODERATION_REQUEST);
    data << quint8(0);
    SendPacket(data);
}
