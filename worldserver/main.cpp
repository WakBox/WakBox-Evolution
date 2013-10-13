#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <iostream>
#include <csignal>
#include <QtSql>

#include "define.h"
#include "databases/database.h"
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "game/chat/commandline.h"

using namespace std;

void stop(int /*s*/)
{
    WorldServer::Instance()->Delete();
    QCoreApplication::exit();
}

int close()
{
    stop(0);
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    if (!WorldServer::Instance()->Initialize())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    Chat::Instance();
    CommandLine commandLine(&a);
    commandLine.start();

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
