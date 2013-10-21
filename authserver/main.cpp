#include <QCoreApplication>
#include <QtCore>
#include <csignal>

#include "Define.h"
#include "AuthServer.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"

void stop(int /*s*/)
{
    AuthServer::Instance()->Delete();
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

    if (!AuthServer::Instance()->Initialize())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "Authserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
