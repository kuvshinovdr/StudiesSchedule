/// @file  config.cpp
#include "config.hpp"
#include "log.hpp"
#include <optional>

namespace studies_schedule
{

    constexpr auto Help      { "--help"sv       };
    constexpr auto Version   { "--version"sv    };
    constexpr auto Attempts  { "--attempts"sv   };
    constexpr auto Input     { "--input"sv      };
    constexpr auto Output    { "--output"sv     };
    constexpr auto Rooms     { "--rooms"sv      };
    constexpr auto Stuff     { "--stuff"sv      };
    constexpr auto Groups    { "--groups"sv     };
    constexpr auto Subjects  { "--subjects"sv   };
    constexpr auto TimeSlots { "--timeslots"sv  };
    constexpr auto Forbidden { "--forbidden"sv  };

    static auto stringToInt(StringView data) noexcept
        -> std::optional<int>
    try
    {
        return std::stoi(String(data));
    }
    catch (...)
    {
        return {};
    }

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
        
        for (auto i = 0zu; i < args.size(); ++i) {
            auto arg  { args[i] }; // обрабатываемый аргумент командной строки
            auto next { i + 1 < args.size()? args[i + 1]: ""sv }; // следующий аргумент командной строки

            if        (arg == Help) {
                config.help = true;
            } else if (arg == Version) {
                config.version = true;
            } else if (arg == Attempts) {
                if (auto attempts = stringToInt(next)) {
                    config.attempts = *attempts;
                    
                    if (config.attempts <= 0) {
                        log::error("Invalid attempts number: {}", config.attempts);
                        config.attempts = 1;
                    }

                    ++i;
                } else {
                    log::error("Failed to parse attempts number: {}", next);
                }
            } // TODO остальные параметры принимают текстовый параметр next, который не требуется парсить.
        }

        return config;
    }

}
