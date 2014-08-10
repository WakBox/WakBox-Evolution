#include <QCoreApplication>
#include <csignal>

#include "Logs/Log.h"
#include "Chat/CommandLine.h"
#include "World/WorldRunnable.h"

CommandLine* commandLine = new CommandLine;
WorldRunnable* worldRunnable = new WorldRunnable;

void stop(int /*s*/)
{
    WorldServer::Instance()->Delete();
    commandLine->exit();
    worldRunnable->exit();
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

    Log::Write(LOG_TYPE_NORMAL, "WW      WW         kk     BBBBB                 ");
    Log::Write(LOG_TYPE_NORMAL, "WW      WW   aa aa kk  kk BB   B   oooo  xx  xx ");
    Log::Write(LOG_TYPE_NORMAL, "WW   W  WW  aa aaa kkkkk  BBBBBB  oo  oo   xx   ");
    Log::Write(LOG_TYPE_NORMAL, " WW WWW WW aa  aaa kk kk  BB   BB oo  oo   xx   ");
    Log::Write(LOG_TYPE_NORMAL, "  WW   WW   aaa aa kk  kk BBBBBB   oooo  xx  xx ");
    Log::Write(LOG_TYPE_NORMAL, "");
    Log::Write(LOG_TYPE_NORMAL, "Wakfu sandbox developped by Sgt Fatality.");
    Log::Write(LOG_TYPE_NORMAL, "Special thanks to : Velocity, scalexm, nightwolf93, Smarken, Crystal.");
    Log::Write(LOG_TYPE_NORMAL, "");

    if (!WorldServer::Instance()->Initialize())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    commandLine->start();
    worldRunnable->start();

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
