/// @file  config.cpp
#include "config.hpp"

namespace studies_schedule
{

    constexpr auto Help     { "--help"sv        };
    constexpr auto Version  { "--version"sv     };

    auto parseCommandLineParameters(int argc, char* argv[])
        -> Config
    {
        auto const params { std::vector<StringView>{ argv + 1, argv + argc } };
        return parseCommandLineParameters(params);
    }

    auto parseCommandLineParameters(std::span<StringView const> args)
        -> Config
    {
        auto config { Config{} };
        
        for (auto arg : args) {
            if (arg == Help) {
                config.help = true;
            } else if (arg == Version) {
                config.version = true;
            }
        }

        return config;
    }

}
