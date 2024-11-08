// 日志管理类
#include "logmanager.h"
#include <QDir>
#include <QDateTime>
#include <QMutexLocker>

// 构造函数
LogManager::LogManager() {
    // 确保日志文件夹存在
    QDir logDir(this->logRoot);
    if (!logDir.exists()) {
        logDir.mkpath(".");
        logDir.mkdir("application");
        logDir.mkdir("database");
        logDir.mkdir("network");
    }
    // 创建日志文件
    logFiles[LOG_APPLICATION] = nullptr;
    logFiles[LOG_DATABASE] = nullptr;
    logFiles[LOG_NETWORK] = nullptr;
    // 创建日志流
    logStreams[LOG_APPLICATION] = nullptr;
    logStreams[LOG_DATABASE] = nullptr;
    logStreams[LOG_NETWORK] = nullptr;
}

// 析构函数
LogManager::~LogManager() {
    // 关闭所有日志文件
    for (auto stream : logStreams) {
        if (stream) {
            delete stream;
        }
    }
    for (auto file : logFiles) {
        if (file) {
            file->close();
            delete file;
        }
    }
}

// 获取单例
LogManager& LogManager::instance() {
    static LogManager instance;
    return instance;
}


// 设置日志类别过滤
void LogManager::setLogCategory(LogCategory category) {
    this->category = category;
}

// 设置日志级别过滤
void LogManager::setLogLevel(LogLevel level) {
    this->level = level;
}

// 记录日志
void LogManager::log(LogCategory category, LogLevel level, const QString &message) {
    // 如果当前日志信息小于于过滤级别，则不记录
    if (level < this->level) {
        return;
    }
    QMutexLocker locker(&mutex);

    // 检查是否需要重新生成日志文件
    checkAndRotateLogFile(category);

    QString logMessage = formatLogMessage(category, level, message);
    if (logStreams.contains(category)) {
        *logStreams[category] << logMessage << "\n";
    }
}

// 检查并重新生成日志文件
void LogManager::checkAndRotateLogFile(LogCategory category) {
    if (logFiles.contains(category)) {
        QString curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QFile *file = logFiles[category];
        
        if (!file) {
            // 如果没有日志文件打开
        } else if (file && !file->fileName().contains(curDate)) {
            // 如果日志文件已打开但日期不符
            file->close();
            delete file;
            delete logStreams[category];
        } else {
            return;
        }

        QString strCategory;
        switch (category) {
            case LOG_APPLICATION : strCategory = "application"; break;
            case LOG_DATABASE : strCategory = "database"; break;
            case LOG_NETWORK : strCategory = "network"; break;
        }

        file = new QFile(logRoot + "/" + strCategory + "/" + generateLogFileName(category));
        if (file->open(QIODevice::Append | QIODevice::Text)) {
            logFiles[category] = file;
            logStreams[category] = new QTextStream(file);
        } else {
            qDebug() << "Failed to open log file for category:" << category;
            // 如果打开日志文件失败，则使用标准输出流
            logStreams[category] = new QTextStream(stdout);
        }
        
    }
}

// 日志消息格式化
QString LogManager::formatLogMessage(LogCategory category, LogLevel level, const QString &message) {
    QString strCategory;
    switch (category) {
        case LOG_APPLICATION : strCategory = "Application"; break;
        case LOG_DATABASE : strCategory = "Database"; break;
        case LOG_NETWORK : strCategory = "Network"; break;
    }

    QString strLevel;
    switch (level) {
        case DEBUG : strLevel = "Debug"; break;
        case INFO : strLevel = "Info"; break;
        case WARNING : strLevel = "Warning"; break;
        case ERROR : strLevel = "Error"; break;
        case CRITICAL : strLevel = "Critical"; break;
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    return QString("[%1] [%2] [%3] %4").arg(timestamp).arg(strCategory).arg(strLevel).arg(message);
}

// 生成日志文件名，根据日志类型和时间
QString LogManager::generateLogFileName(LogCategory category) {
    QString strCategory;
    switch (category) {
        case LOG_APPLICATION : strCategory = "Application"; break;
        case LOG_DATABASE : strCategory = "Database"; break;
        case LOG_NETWORK : strCategory = "Network"; break;
    }

    QString dateStr = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    return QString("%1_%2.log").arg(strCategory).arg(dateStr);
}
