#SOURCES += $$PWD/*.cpp
HEADERS += $$PWD/*.h

include(Configuration/Configuration.pri)
include(Cryptography/Cryptography.pri)
include(Databases/Databases.pri)
include(Logs/Logs.pri)
include(Network/Network.pri)
include(Packets/Packets.pri)
include(Utils/Utils.pri)
