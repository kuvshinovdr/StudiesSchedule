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
        // TODO
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
        SUBCASE("proper coloring  1")
        {
            AdjacencyList graph = {{1, 2},
                                   {0, 2},
                                   {0, 1, 3, 6},
                                   {2, 4, 5},
                                   {3, 5, 6},
                                   {3, 4},
                                   {2, 4}};
            ForbiddenColors forbidden(3);
            Coloring startColoring = { 1, 2, 1, 2, 1, 2, 2 };
            Color maxColor = computeVertexColoring(graph, forbidden, startColoring);
            
            CHECK(maxColor == 3);
            CHECK(isProperVertexColoring(triangle, startColoring) == true);
        }

        SUBCASE("proper coloring 2")
        {
            AdjacencyList graph2 = {{1, 3},
                                    {0, 2},
                                    {1, 3},
                                    {0, 2}};

            ForbiddenColors forbidden2(4);
            Coloring startColoring = { 1, 1, 1, 1 };

            Color maxColor = computeVertexColoring(graph2, forbidden2, startColoring);

            CHECK(maxColor <= 2);
            CHECK(isProperVertexColoring(graph2, startColoring) == true);
        }

        SUBCASE("respects forbidden colors")
        {
            AdjacencyList graph3 = {{1, 2},
                                    {0, 2},
                                    {0, 1}};

            ForbiddenColors forbidden(3);
            forbidden[0].insert(1);
            forbidden[1].insert(2);
            forbidden[2].insert(3);

            Coloring startColoring = { 2, 3, 1 }; 
            Color maxColor = computeVertexColoring(graph3, forbidden, startColoring);

            CHECK(startColoring[0] != 1);
            CHECK(startColoring[1] != 2);
            CHECK(startColoring[2] != 3);
            CHECK(isProperVertexColoring(graph3, startColoring) == true);
        }

        SUBCASE("empty graph")
        {
            AdjacencyList empty = {};
            ForbiddenColors forbiddenEmpty(0);
            Coloring coloring = {};

            Color maxColor = computeVertexColoring(empty, forbiddenEmpty, coloring);

            CHECK(maxColor == 0);
            CHECK(coloring.empty());
        }

        SUBCASE("single vertex")
        {
            AdjacencyList single = { {} };
            ForbiddenColors forbiddenSingle(1);
            Coloring coloring = { 1 };

            Color maxColor = computeVertexColoring(single, forbiddenSingle, coloring);

            CHECK(maxColor == 1);
            CHECK(coloring[0] == 1);
        }

    }

}