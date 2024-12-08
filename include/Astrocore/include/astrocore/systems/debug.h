#ifndef DEBUG_H
#define DEBUG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Astrocore
{
    class Debug
    {

    public:
        static void init()
        {
            try
            {
                //auto logger = spdlog::basic_logger_mt("basic_logger", "basic-log.txt");
                //spdlog::set_default_logger(logger);
                //spdlog::info("Initialized logger!");

                auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                console_sink->set_level(spdlog::level::debug);

                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("debug_log.txt", true);
                file_sink->set_level(spdlog::level::debug);

                spdlog::logger logger("multi_sink", {console_sink, file_sink});
                logger.set_level(spdlog::level::debug);
                //logger.warn("this should appear in both console and file");
                //logger.info("this message should not appear in the console, only in the file");
            }
            catch (const spdlog::spdlog_ex &ex)
            {
                spdlog::error("Log init failed: " + std::string(ex.what()));
            }
            spdlog::set_pattern("[%H:%M:%S] %^%l%$ %v");
        }
        // Log a line to the console/file log
        static inline void LogLine(std::string logEntry)
        {
            spdlog::info(logEntry);
        };

        static inline void LogWarning(std::string warningEntry)
        {
            spdlog::warn(warningEntry);
        }

        static inline void LogError(std::string errorEntry)
        {
            spdlog::error(errorEntry);
        }
        // TODO: Add writing to files
        // TODO: Add assert functionality
    };
}

// Macros
#define DBG_LOG(...) ::Astrocore::Debug::LogLine(__VA_ARGS__)
#define DBG_WARN(...) ::Astrocore::Debug::LogWarning(__VA_ARGS__)
#define DBG_ERR(...) ::Astrocore::Debug::LogError(__VA_ARGS__)
#endif