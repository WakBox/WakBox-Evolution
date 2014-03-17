#ifndef LOG_H
#define LOG_H

#include <QtCore>
#include <iostream>
#include "Log.h"
#include "Configuration/ConfigMgr.h"
#include "Utils/Singleton.h"

using namespace std;

enum LogType
{
    LOG_TYPE_NORMAL = 0,
    LOG_TYPE_DETAIL,
    LOG_TYPE_DEBUG
};

class Log : public Singleton<Log>
{
public:
    Log();
    ~Log();

    static QString GetLogTypeString(LogType logType)
    {
        switch(logType)
        {
        case LOG_TYPE_DETAIL:
            return "[ Detail ] ";
        case LOG_TYPE_DEBUG:
            return "[ Debug ] ";
        case LOG_TYPE_NORMAL:
        default:
            return "";
        }
    }

    void Initialize(ushort logConsoleLevel, ushort logFileLevel, QString logFile);
    void OpenFile(QString fileName);
    void WriteLog(QString logMessage, LogType logType);
    static void Write(LogType logType, QString message, ...);

private:
    LogType m_logTypeConsole;
    LogType m_logTypeFile;
    QFile* m_file;
};

#endif
