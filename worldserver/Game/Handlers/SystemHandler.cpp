#include "Server/WorldSession.h"

void WorldSession::SendSystemConfiguration()
{
    // TMP Config
    QMap<quint16, QString> config;
    config[16] = "http://localhost/wakverif.php";

    WorldPacket data(SMSG_SYSTEM_CONFIGURATION);
    data.StartBlock<int>();
    {
        data << (quint32) config.size();
        for (QMap<quint16, QString>::ConstIterator itr = config.begin(); itr != config.end(); ++itr)
        {
            data << (quint16) itr.key();
            data.WriteString(itr.value(), STRING_SIZE_4);
        }

    }
    data.EndBlock<int>();

    SendPacket(data);
}
