/// @file  log.hpp
/// @brief API средств протоколирования.
#ifndef STUDIES_SCHEDULE_LOG_HPP
#define STUDIES_SCHEDULE_LOG_HPP

#include "error_fwd.hpp"
#include "string_operations_fwd.hpp"
#include <format>
#include <cstdlib>

namespace studies_schedule::log
{

    enum class MessageType
    {
        Fatal,
        Error,
        Warning,
        Info,
        Debug,
    };

    void put(MessageType, String const&);

    template <typename... Args>
    void fatal(std::format_string<Args...> fmt, Args&&... args)
    {
        put(MessageType::Fatal, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args)
    {
        put(MessageType::Error, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args)
    {
        put(MessageType::Warning, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args)
    {
        put(MessageType::Info, std::format(fmt, std::forward<Args>(args)...));
    }

#ifndef NDEBUG
    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args)
    {
        put(MessageType::Debug, std::format(fmt, std::forward<Args>(args)...));
    }
#else
    template <typename... Args>
    void debug(Args&&...)
    {
        // Пусто.
    }
#endif

}

#endif//STUDIES_SCHEDULE_LOG_HPP
