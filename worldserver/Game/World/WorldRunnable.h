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
        quint64 currentTime, previousSleepTime = 0;
        quint64 previousTime = QDateTime::currentMSecsSinceEpoch();

        while (World::Instance()->IsRunning())
        {
            currentTime = QDateTime::currentMSecsSinceEpoch();
            quint64 diff = currentTime - previousTime;

            World::Instance()->Update(diff);
            previousTime = currentTime;

            if (diff <= 1 + previousSleepTime)
            {
                previousSleepTime = 1 + previousSleepTime - diff;
                msleep(previousSleepTime);
            }
            else
                previousSleepTime = 0;
        }

        qDebug() << "done";
    }
};

#endif
