/// @file  config.cpp
#include "config.hpp"

namespace studies_schedule
{

    auto parseCommandLineParameters(int argc, char* argv[])
        -> Config
    {
        auto const params { std::vector<StringView>{ argv + 1, argv + argc } };
        return parseCommandLineParameters(params);
    }

    auto parseCommandLineParameters(std::span<StringView const> params)
        -> Config
    {
        auto config { Config{} };
        // TODO
        return config;
    }

}
