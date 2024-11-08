// 日志系统
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QString>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QMutex>

// 日志类别
enum LogCategory {
    LOG_APPLICATION,
    LOG_DATABASE,
    LOG_NETWORK
};

// 日志级别
enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class LogManager {
public:
    // 单例模式
    static LogManager& instance();
    // 禁止拷贝构造和赋值
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    // 设置日志类别和级别
    void setLogCategory(LogCategory category);
    void setLogLevel(LogLevel level);
    // 记录日志
    void log(LogCategory category, LogLevel level, const QString &message);
    // 检查是否需要重新生成日志文件
    void checkAndRotateLogFile(LogCategory category);

private:
    QString logRoot = "logs";                       // 日志文件根目录
    LogCategory category;                           // 日志类别过滤
    LogLevel level;                                 // 日志级别过滤 
    QMap<LogCategory, QFile*> logFiles;             // 日志文件
    QMap<LogCategory, QTextStream*> logStreams;     // 日志流
    QMutex mutex;                                   // 日志线程锁

    // 私有构造函数，防止外部实例化
    LogManager();
    ~LogManager();

    // 生成日志文件名
    QString generateLogFileName(LogCategory category);
    // 日志消息格式化
    QString formatLogMessage(LogCategory category, LogLevel level, const QString &message);
    
};

#endif // LOGMANAGER_H