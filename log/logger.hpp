#ifndef FDOGLOGGER_H
#define FDOGLOGGER_H

#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

namespace fdog
{

    enum class LogLevel
    {
        Error,
        Warn,
        Info,
        Debug,
        Trace
    };

    class Logger
    {
    public:
        static Logger &getInstance();

        void initLogConfig(const std::string &configFile);

        void log(LogLevel level, const std::string &message);

    private:
        Logger();
        ~Logger();

        std::string getCurrentTime();
        // 检查文件大小并在必要时创建新文件,返回是否新建文件
        bool checkAndRotateLogFile();

        void ManageLogFile( );
        std::string getLogLevelString(LogLevel level);

        std::ofstream logFile;
        std::mutex mtx;
        LogLevel fileLogLevel;
        LogLevel terminalLogLevel;
        std::size_t maxLogFiles;
        std::size_t maxFileSize;
        fs::path logFileName;
        fs::path logDirPath;
    };

#define FDOG_LOG(level, message) \
    fdog::Logger::getInstance().log(level, message)

#define FDOG_ERROR(message) FDOG_LOG(fdog::LogLevel::Error, message)
#define FDOG_WARN(message) FDOG_LOG(fdog::LogLevel::Warn, message)
#define FDOG_INFO(message) FDOG_LOG(fdog::LogLevel::Info, message)
#define FDOG_DEBUG(message) FDOG_LOG(fdog::LogLevel::Debug, message)
#define FDOG_TRACE(message) FDOG_LOG(fdog::LogLevel::Trace, message)

}

#endif
