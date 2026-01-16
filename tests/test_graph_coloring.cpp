/// @file  test_graph_coloring.cpp
#include <graph_coloring.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("graph coloring")
{

    TEST_CASE("isAdjacencyListValid")
    {
        // TODO
    }

    TEST_CASE("colorsAreValid")
    { 
        {
            auto coloring        { Coloring{1, 3, 2, 4} };
            auto forbiddenColors { ForbiddenColors{{2,4}, {1,2}, {4,3}, {1,2,3}} };
            
            CHECK(colorsAreValid(coloring, forbiddenColors));
        }
        
        {
            auto coloring        { Coloring{5, 6, 7, 8} };
            auto forbiddenColors { ForbiddenColors{{6,7}, {7,8}, {6,8}, {6,7,8}} };
            
            CHECK(!colorsAreValid(coloring, forbiddenColors));
        }
    }

    TEST_CASE("isProperVertexColoring")
    {
        // TODO
    }
    
    TEST_CASE("randomColoring")
    {
        // TODO
    }

    TEST_CASE("computeVertexColoring")
    {
        // TODO
    }

}
