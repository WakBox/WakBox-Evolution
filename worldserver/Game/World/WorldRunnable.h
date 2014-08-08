#ifndef WORLDRUNNABLE_H
#define WORLDRUNNABLE_H

#include <QtCore>
#include "World.h"

class WorldRunnable : public QThread
{
    Q_OBJECT
public:
    WorldRunnable(QObject* parent = 0) : QThread(parent) {}

    virtual void run()
    {
        quint64 currentTime = 0;
        quint64 previousTime = QDateTime::currentMSecsSinceEpoch();
        qDebug() << World::Instance()->IsRunning();
        while (World::Instance()->IsRunning())
        {
            currentTime = QDateTime::currentMSecsSinceEpoch();
            quint64 diff = currentTime - previousTime;

            World::Instance()->Update(diff);
        }

        qDebug() << "done";
    }
};

#endif
