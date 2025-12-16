#include "engine/Log.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace engine
{

    namespace
    {

        std::string FormatTimestamp()
        {
            using clock = std::chrono::system_clock;
            const auto now = clock::now();
            const std::time_t time = clock::to_time_t(now);
            std::tm tm{};
#if defined(_WIN32)
            localtime_s(&tm, &time);
#else
            localtime_r(&time, &tm);
#endif

            std::ostringstream oss;
            oss << std::put_time(&tm, "%H:%M:%S");
            return oss.str();
        }

        const char *ToString(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::SUCCESS:
                return "SUCCESS";
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Warning:
                return "WARN";
            case LogLevel::Error:
                return "ERROR";
            }
            return "UNKNOWN";
        }

    } // namespace

    void Log(LogLevel level, std::string_view message)
    {
        std::cout << "[" << FormatTimestamp() << "] "
                  << ToString(level) << " | "
                  << message << std::endl;
    }

} // namespace engine
