#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "logger.hpp"

namespace fs = std::filesystem;

namespace fdog
{
    Logger &Logger::getInstance()
    {
        static Logger instance;
        return instance;
    }

    Logger::Logger() : fileLogLevel(LogLevel::Info), terminalLogLevel(LogLevel::Info), maxFileSize(100)
    {
    }
    Logger::~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void Logger::initLogConfig(const std::string &configFile)
    {
        std::ifstream file(configFile);
        if (!file.is_open())
        {
            std::cerr << "Failed to open logConfig file\n";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string key, value;
            if (iss.peek() == '#')
            {
                continue;
            }
            if (std::getline(iss, key, '=') && std::getline(iss, value))
            {
                if (key == "logDirPath")
                {
                    logDirPath = value;
                    logFileName = logDirPath / (getCurrentTime() + ".log");
                    logFile.open(logFileName, std::ios::app);
                    if (!logFile.is_open())
                    {
                        std::cerr << "Failed to open log file: " << logFileName << std::endl;
                    }
                    else
                    {
                        // 如果文件成功打开，可以写入数据
                        logFile << "This is a log entry appended to the file.\n";
                    }
                }
                else if (key == "fileLogLevel")
                {
                    try
                    {
                        fileLogLevel = static_cast<LogLevel>(std::stoi(value));
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "Invalid fileLogLevel value: " << value << std::endl;
                    }
                    catch (const std::out_of_range &e)
                    {
                        std::cerr << "fileLogLevel value out of range: " << value << std::endl;
                    }
                }
                else if (key == "terminalLogLevel")
                {
                    try
                    {
                        terminalLogLevel = static_cast<LogLevel>(std::stoi(value));
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "Invalid terminalLogLevel value: " << value << std::endl;
                    }
                    catch (const std::out_of_range &e)
                    {
                        std::cerr << "terminalLogLevel value out of range: " << value << std::endl;
                    }
                }
                else if (key == "maxLogFiles")
                {
                    maxLogFiles = static_cast<size_t>(std::stoi(value));
                }
            }
        }
    }

    std::string Logger::getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H_%M_%S");
        return ss.str();
    }

    std::string Logger::getLogLevelString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Error:
            return "ERROR";
        case LogLevel::Warn:
            return "WARN";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Trace:
            return "TRACE";
        default:
            return "UNKNOWN";
        }
    }
    // 检查文件大小并在必要时创建新文件
    bool Logger::checkAndRotateLogFile()
    {
        if (fs::exists(logFileName) && fs::file_size(logFileName) >= maxFileSize * 1024)
        {
            if (logFile.is_open())
            {
                logFile.close(); // 关闭当前文件
            }
            sleep(2);
            std::string today = getCurrentTime();

            // 构建日志文件的完整路径
            logFileName = logDirPath / (today + ".log");

            // 打开文件进行追加（如果文件不存在则创建）
            logFile.open(logFileName, std::ios::app);
            if (!logFile.is_open())
            {
                std::cerr << "Failed to open log file: " << logFileName << std::endl;
                return true;
            }
            logFile << "Log entry for " << today << std::endl;
            return true;
        }
        return false;
    }

    void Logger::log(LogLevel level, const std::string &message)
    {
        std::string logMessage = "[" + getCurrentTime() + "]\t[" + getLogLevelString(level) + "] " + message + "\n";
        bool createFile = false;
        if (level <= fileLogLevel && logFile.is_open())
        {
            std::lock_guard<std::mutex> lock(mtx);
            createFile = checkAndRotateLogFile();
            logFile << logMessage;
        }
        if (createFile)
        {
            ManageLogFile();
        }
        else if (!logFile.is_open())
        {
            std::cout << (int)fileLogLevel << std::endl;
        }

        if (level <= terminalLogLevel)
        {
            // std::cout << logMessage;
        }
    }
    void Logger::ManageLogFile()
    {
        // 检查并删除最旧的日志文件（如果超过五个）
        std::vector<fs::path> logFiles;
        for (const auto &entry : fs::directory_iterator(logDirPath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".log")
            {
                logFiles.push_back(entry.path());
            }
        }

        // 如果文件数超过五个，则删除最旧的
        if (logFiles.size() > maxLogFiles)
        { // 按文件名（日期）排序（需要转换为可排序的格式）
            std::sort(logFiles.begin(), logFiles.end(), [](const fs::path &a, const fs::path &b)
                      {
                        std::string aDate = a.stem().string();
                        std::string bDate = b.stem().string();
                        return aDate < bDate; });
            for (auto it = logFiles.begin(); it != logFiles.begin() + (logFiles.size() - 5); ++it)
            {
                fs::remove(*it);
                std::cout << "Deleted old log file: " << *it << std::endl;
                logFile << "Deleted old log file: " << *it << std::endl;
            }
        }
    }
}