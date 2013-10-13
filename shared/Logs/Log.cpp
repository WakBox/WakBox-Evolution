#include "Log.h"

template<> Log*  Singleton<Log>::m_instance = 0;

Log::Log()
{
    m_logTypeConsole = LOG_TYPE_NORMAL;
    m_logTypeFile = LOG_TYPE_NORMAL;
    m_file = NULL;
}

Log::~Log()
{
    if(m_file)
        m_file->close();
}

void Log::Init(ushort logConsoleLevel, ushort logFileLevel, QString logFile)
{
    m_logTypeConsole = LogType(logConsoleLevel);
    m_logTypeFile = LogType(logFileLevel);
    OpenFile(logFile);
}

void Log::OpenFile(QString fileName)
{
    m_file = new QFile(fileName, this);
    if(m_file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString error = m_file->errorString();
    delete m_file;
    m_file = NULL;

    Log::Write(LOG_TYPE_NORMAL, "Cannot open log file %s : %s", fileName.toLatin1().data(), error.toLatin1().data());
}

void Log::WriteLog(QString logMessage, LogType logType)
{
    if (logType <= m_logTypeConsole)
        cout << logMessage.toLatin1().data() << endl;

    if(m_file && logType <= m_logTypeFile)
    {
        m_file->write(logMessage.toLatin1() + "\n");
        m_file->flush();
    }
}

void Log::Write(LogType logType, QString message, ...)
{
    QString logTypeString = Log::GetLogTypeString(logType);

    va_list ap;
    va_start(ap, message);
    QString logMessage;
    logMessage.vsprintf(message.toLatin1().data(), ap);

    logMessage = logTypeString + logMessage;
    Log::Instance()->WriteLog(logMessage, logType);
}
