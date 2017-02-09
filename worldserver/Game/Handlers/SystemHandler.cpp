#include "Server/WorldSession.h"
#include "Utils/Util.h"

void WorldSession::SendSystemConfiguration()
{
    // TMP Config
    QMap<quint16, QString> config;
    config[16] = "http://localhost/auth.soap";
    config[17] = "http://localhost/account.soap";
    config[18] = "http://localhost/shop.soap";

    WorldPacket data(SMSG_SYSTEM_CONFIGURATION);
    data.WriteRawBytes(Utils::FromHexString("00 00 01 F6 00 00 00 23 00 02 00 00 00 01 30 00 03 00 00 00 0C 45 75 72 6F 70 65 2F 50 61 72 69 73 00 05 00 00 00 02 66 72 00 06 00 00 00 04 74 72 75 65 00 07 00 00 00 03 32 30 30 00 08 00 00 00 2C 31 3B 32 3B 33 3B 34 3B 35 3B 36 3B 37 3B 38 3B 39 3B 31 30 3B 31 31 3B 31 32 3B 31 33 3B 31 34 3B 31 36 3B 31 37 3B 31 38 3B 31 39 00 09 00 00 00 00 00 0B 00 00 00 05 66 61 6C 73 65 00 0C 00 00 00 05 66 61 6C 73 65 00 0D 00 00 00 04 74 72 75 65 00 0F 00 00 00 04 74 72 75 65 00 10 00 00 00 30 68 74 74 70 3A 2F 2F 61 70 69 2E 61 6E 6B 61 6D 61 2E 63 6F 6D 2F 47 61 6D 65 2F 61 75 74 68 65 6E 74 69 66 69 63 61 74 69 6F 6E 2E 73 6F 61 70 00 11 00 00 00 27 68 74 74 70 3A 2F 2F 61 70 69 2E 61 6E 6B 61 6D 61 2E 63 6F 6D 2F 47 61 6D 65 2F 61 63 63 6F 75 6E 74 2E 73 6F 61 70 00 12 00 00 00 24 68 74 74 70 3A 2F 2F 61 70 69 2E 61 6E 6B 61 6D 61 2E 63 6F 6D 2F 47 61 6D 65 2F 73 68 6F 70 2E 73 6F 61 70 00 CA 00 00 00 05 66 61 6C 73 65 00 D3 00 00 00 05 66 61 6C 73 65 01 95 00 00 00 00 01 96 00 00 00 04 74 72 75 65 01 97 00 00 00 05 66 61 6C 73 65 01 9C 00 00 00 04 74 72 75 65 01 9D 00 00 00 0C 57 41 4B 46 55 5F 49 4E 47 41 4D 45 01 9E 00 00 00 00 01 9F 00 00 00 00 01 A1 00 00 00 04 74 72 75 65 01 A2 00 00 00 05 66 61 6C 73 65 01 A3 00 00 00 05 66 61 6C 73 65 01 A4 00 00 00 01 31 01 A5 00 00 00 04 74 72 75 65 01 A9 00 00 00 04 74 72 75 65 01 AC 00 00 00 05 66 61 6C 73 65 01 AF 00 00 00 04 74 72 75 65 02 5A 00 00 00 05 66 61 6C 73 65 02 5B 00 00 00 04 74 72 75 65 02 62 00 00 00 01 30 02 63 00 00 00 04 74 72 75 65"));

    /*data.StartBlock<int>();
    {
        data << (quint32) config.size();
        for (QMap<quint16, QString>::ConstIterator itr = config.begin(); itr != config.end(); ++itr)
        {
            data << (quint16) itr.key();
            data.WriteString(itr.value(), STRING_SIZE_4);
        }

    }
    data.EndBlock<int>();*/

    SendPacket(data);
}
