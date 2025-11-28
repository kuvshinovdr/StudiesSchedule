/// @file config.hpp
#ifndef STUDIES_SCHEDULE_CONFIG_HPP
#define STUDIES_SCHEDULE_CONFIG_HPP

#include "string_operations_fwd.hpp"
#include <vector>
#include <span>

namespace studies_schedule
{

    struct Config
    {
        bool    help       { false };
        bool    version    { false };

        String  rooms      { "rooms.csv"s     };
        String  groups     { "groups.csv"s    };
        String  stuff      { "stuff.csv"s     };
        String  subjects   { "subjects.csv"s  };
        String  timeslots  { "timeslots.csv"s };
        String  forbidden  { "forbidden.csv"s };
        
        String  input      { "./" };
        String  output     { "./studies_schedule/" };
    };

    [[nodiscard]] auto parseCommandLineParameters(std::span<StringView const> params)
        -> Config;

    [[nodiscard]] auto parseCommandLineParameters(int argc, char* argv[])
        -> Config;

}

#endif//STUDIES_SCHEDULE_CONFIG_HPP
