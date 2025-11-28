#include <config.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("config")
{

    TEST_CASE("no args")
    {
        auto config = parseCommandLineParameters({});
        
        CHECK(!config.version);
        CHECK(!config.help);
    }

}