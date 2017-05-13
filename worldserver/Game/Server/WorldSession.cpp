#include "WorldSession.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Entities/Character/Character.h"
#include "World/World.h"

WorldSession::WorldSession(QTcpSocket *socket) : SocketHandler(socket)
{
    m_accountInfos.id = 0;
    m_accountInfos.username = QString();
    m_accountInfos.pseudo = QString();
    m_accountInfos.gmLevel = 0;
    m_accountInfos.subscriptionTime = 0;
    m_accountInfos.charactersCount = 0;

    SetCharacter(NULL);

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnClose()));
    Log::Write(LOG_TYPE_NORMAL, "New incoming connection from %s", m_socket->peerAddress().toString().toLatin1().data());
}

WorldSession::~WorldSession()
{
    qDebug() << "delete m_character";
    delete m_character;
}

void WorldSession::ProcessPacket()
{
    QDataStream in(m_socket);

    while (m_socket->bytesAvailable())
    {
        if (m_packetSize == 0)
        {
            if (m_socket->bytesAvailable() < (qint64)sizeof(quint16))
                return;

            in >> m_packetSize;
        }

        if (m_socket->bytesAvailable() < (m_packetSize - 2))
            return;

        qint8 unk;
        quint16 opcode;
        QByteArray data;

        in >> unk;
        in >> opcode;
        data = in.device()->read((qint64)(m_packetSize - 5));

        if (OpcodeTable::Exists(opcode))
        {
            OpcodeHandler opcodeHandler = OpcodeTable::Get(opcode);
            Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, m_packetSize);

            WorldPacket packet(opcode, data);

            switch (opcodeHandler.status)
            {
            case STATUS_UNHANDLED:
                Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, data.size());
                break;
            case STATUS_NEVER:
                Log::Write(LOG_TYPE_DEBUG, "Received not allowed packet <%u> (size : %u).", opcode, data.size());
                break;
            default:
                // TODO manage status STATUS_IN_WORLD and STATUS_TRANSFER
                if (opcodeHandler.status == STATUS_ALWAYS ||
                    (opcodeHandler.status == STATUS_AUTHED && GetAccountInfos().id != 0))
                {
                    (this->*opcodeHandler.handler)(packet);
                    Log::Write(LOG_TYPE_DEBUG, "Received packet opcode %s <%u> (size : %u).", opcodeHandler.name.toLatin1().data(), opcode, data.size());
                }
                else
                {
                    // Report IP too
                    Log::Write(LOG_TYPE_DEBUG, "Warning ! Received packet with wrong status (hack !?) <%u> (size : %u).", opcode, data.size());
                    OnClose();
                }
                break;
            }
        }
        else
            Log::Write(LOG_TYPE_DEBUG, "Received unhandled packet <%u> (size : %u).", opcode, m_packetSize);

        m_packetSize = 0;
    }
}

void WorldSession::SendPacket(WorldPacket& data)
{
    data.WriteHeader();
    m_socket->write(data.GetPacket());

    Log::Write(LOG_TYPE_DEBUG, "Send packet %s <%u> (size : %u).", OpcodeTable::Get(data.GetOpcode()).name.toLatin1().data(), data.GetOpcode(), data.GetPacket().size());
}

void WorldSession::OnClose()
{
    Character* character = GetCharacter();
    if (character)
    {
        character->SetInWorld(false);
        character->SaveToDB();
        qDebug() << "Character " << character->GetName() << " saved to DB.";
    }

    World::Instance()->RemoveSession(this);
    SocketHandler::OnClose();
}
