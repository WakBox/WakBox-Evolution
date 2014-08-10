#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QtCore>
#include <iostream>

#include "Chat.h"
#include "World/World.h"

using namespace std;

class CommandLine : public QThread
{
    Q_OBJECT
public:
    CommandLine(QObject* parent = 0) : QThread(parent) {}

    virtual void run()
    {
        while (World::Instance()->IsRunning())
        {
            cout << "Wakbox>";
            fflush(stdout);

            char* command_str;
            char commandbuff[256];

            command_str = fgets(commandbuff, sizeof(commandbuff), stdin);

            if (command_str != NULL)
            {
                for (int x=0; command_str[x]; ++x)
                    if (command_str[x] == '\r' || command_str[x] == '\n')
                    {
                        command_str[x] = 0;
                        break;
                    }

                if (!*command_str)
                    continue;

                QString command = QString::fromStdString(command_str);

                if (command.isEmpty())
                    continue;

                fflush(stdout);
                Chat::Instance()->ParseCommand(command);
            }
            else if (feof(stdin))
            {
                // Close WorldServer, etc. ?????
                qDebug() << "test";
            }
        }
    }
};

#endif
