/// @file  log_test_implementation.cpp
/// @brief Замещающая реализация для log.hpp в проекте модульных тестов.
#include <log.hpp>
#include <doctest.h>

namespace studies_schedule::log
{

    void put(MessageType type, String const& msg)
    {
        switch (type) {
        using enum MessageType;
        case Fatal:
            { FAIL(msg); }
            break;
        case Error:
            { FAIL_CHECK(msg); }
            break;
        case Warning:
            { MESSAGE(msg); }
            break;
        case Info:
            { INFO(msg); }
            break;
        case Debug:
            { INFO(msg); }
            break;
        }
    }

}
