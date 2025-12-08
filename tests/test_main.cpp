#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_SUITE("main")
{
    TEST_CASE("report date and time")
    {
        MESSAGE("Built on " __DATE__ " " __TIME__);
    }
}
