#include <QCoreApplication>
#include <csignal>

#include "AuthServer.h"
#include "Logs/Log.h"
#include "Define.h"

void stop(int /*s*/)
{
    sAuthServer->Delete();
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
    Log::Write(LOG_TYPE_NORMAL, "Special thanks to : Boredom, Velocity, scalexm, nightwolf93, Smarken, Crystal, Totomakers.");
    Log::Write(LOG_TYPE_NORMAL, "");

    if (!sAuthServer->Initialize())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::AuthServer started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
