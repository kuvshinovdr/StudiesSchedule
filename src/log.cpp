/// @file  log.cpp
#include "log.hpp"
#include <iostream>

namespace studies_schedule::log
{

    [[nodiscard]] static auto loggingPrefix(MessageType type)
        -> StringView
    {
        switch (type)
        {
        using enum MessageType;
        case Fatal:
            return "FATAL "sv;
        case Error:
            return "ERROR "sv;
        case Warning:
            return "WARN  "sv;
        case Info:
            return "INFO  "sv;
        case Debug:
            return "DEBUG "sv;
        }

        return {};
    }

    void put(MessageType type, String const& msg)
    {
        std::clog << loggingPrefix(type) << msg << '\n';
    }

}
