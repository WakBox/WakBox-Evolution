#SOURCES += $$PWD/*.cpp
HEADERS += $$PWD/*.h

include(Configuration/Configuration.pri)
include(Databases/Databases.pri)
include(Logs/Logs.pri)
include(Network/Network.pri)
include(Opcodes/Opcodes.pri)
include(Packets/Packets.pri)
include(Utils/Utils.pri)
