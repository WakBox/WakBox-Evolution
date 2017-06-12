#include "TopologyMgr.h"
#include "SimpleBinaryReader.h"
#include "Logs/Log.h"
#include "Utils/Util.h"

template<> TopologyMgr*  Singleton<TopologyMgr>::m_instance = 0;

TopologyMgr::TopologyMgr()
{

}

TopologyMgr::~TopologyMgr()
{

}

void TopologyMgr::LoadTopology()
{
    QDir dir("maps/tplg");
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    if (!dir.exists())
    {
        qDebug() << "Folder maps/tplg not found!";
        return;
    }

    QTime t;
    t.start();
    Log::Write(LOG_TYPE_NORMAL, ">> Loading maps topology...");

    QFileInfoList mapList = dir.entryInfoList();
    for (int i = 0; i < mapList.size(); ++i)
    {
        quint16 mapId = mapList.at(i).fileName().remove(".jar").toUShort();
        QuaZip archive("maps/tplg/" + mapList.at(i).fileName());

        if (!archive.open(QuaZip::mdUnzip))
        {
            qDebug() << "Error while opening maps/tplg/" + mapList.at(i).fileName();
            continue;
        }

        QuaZipFile file(&archive);

        TopologyMapHash topologyMapHash;

        for (bool f = archive.goToFirstFile(); f; f = archive.goToNextFile())
        {
            QString filePath = archive.getCurrentFileName();

            if (filePath.contains("META") || filePath.contains("coord"))
                continue;

            file.open(QIODevice::ReadOnly);
            QByteArray ba = file.readAll();
            file.close();

            short mapx = filePath.split("_").at(0).toShort();
            short mapy = filePath.split("_").at(1).toShort();

            SimpleBinaryReader* reader = new SimpleBinaryReader(ba);
            qint8 type = reader->readByte();
            TopologyMap* mapTopology = nullptr;

            switch (type)
            {
                case 0: mapTopology = new TopologyMapA(reader); break;
                case 1: mapTopology = new TopologyMapB(reader); break;
                case 2: mapTopology = new TopologyMapBi(reader); break;
                case 3: mapTopology = new TopologyMapC(reader); break;
                case 4: mapTopology = new TopologyMapCi(reader); break;
                case 5: mapTopology = new TopologyMapD(reader); break;
                default:
                    return;
            }

            mapTopology->read();

            //int offsetx = (mapx * 18) + x;
            //int offsety = (mapy * 18) + y;

            //qint8 res = mapTopology->isCellBlocked(offsetx, offsety);

            topologyMapHash[Utils::getIntFromTwoInt(mapx, mapy)] = mapTopology;
        }

        archive.close();
        m_topologyMaps[mapId] = topologyMapHash;
    }

    Log::Write(LOG_TYPE_NORMAL, ">> Loaded %u maps topology in %u ms.", m_topologyMaps.count(), t.elapsed());
}
