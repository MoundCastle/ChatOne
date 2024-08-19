#include <iostream>
#include "logger.hpp"

int main()
{
    // 初始化日志配置
    const std::string configFile = "/home/zdy/MyDir/CPPprojects/test/log/logConfig.ini"; // 修改为你的配置文件路径
    fdog::Logger::getInstance().initLogConfig(configFile);
    int i = 2000;
    while (i > 0)
    {
        i--;
        // 记录一些日志消息
        fdog::Logger::getInstance().log(fdog::LogLevel::Info, "This is an info message. ");
        fdog::Logger::getInstance().log(fdog::LogLevel::Warn, "This is a warning message. ");
        fdog::Logger::getInstance().log(fdog::LogLevel::Error, "This is an error message. ");
        fdog::Logger::getInstance().log(fdog::LogLevel::Debug, "This is an debug message. ");
        fdog::Logger::getInstance().log(fdog::LogLevel::Trace, "This is an trace message. ");
    }
    return 0;
}