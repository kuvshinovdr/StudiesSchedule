/// @file  test_solve.cpp
#include <solve.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("solve")
{

    TEST_CASE("simpleSanityCheck")
    {
        // TODO
    }

    TEST_CASE("findUnassignedSubjects")
    {
        // TODO
    }

    TEST_CASE("isBetter")
    {
        auto small { Assignments(3) };
        auto big   { Assignments(5) };
        auto task  { Task{} };
        
        CHECK(isBetter(big, small, task));
    }

}