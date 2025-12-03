#include <config.hpp>
#include <doctest.h>
#include <array>

using namespace studies_schedule;

TEST_SUITE("config")
{

    TEST_CASE("no args")
    {
        auto config { parseCommandLineParameters({}) };
        
        CHECK(!config.version);
        CHECK(!config.help);
        CHECK(config.attempts > 0);
    }

    TEST_CASE("version")
    {
        auto config { parseCommandLineParameters(std::array{ "--version"sv }) };

        CHECK(config.version);
        CHECK(!config.help);

        config = parseCommandLineParameters(std::array{ "--versionn"sv, "hfjah"sv, "--version"sv });
        CHECK(config.version);
        CHECK(!config.help);
    }

    TEST_CASE("help")
    {
        auto config { parseCommandLineParameters(std::array{ "--help"sv }) };

        CHECK(!config.version);
        CHECK(config.help);

        config = parseCommandLineParameters(std::array{ "--helpp"sv, "hfjah"sv, "--help"sv });
        CHECK(!config.version);
        CHECK(config.help);
    }

    TEST_CASE("attempts")
    {
        auto config { parseCommandLineParameters(std::array{ "--attempts"sv, " 111 "sv }) };
        
        CHECK(config.attempts == 111);
    }

}