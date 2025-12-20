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
        // TODO
    }

    TEST_CASE("isProperVertexColoring") {
        using namespace studies_schedule;
        
        SUBCASE("Empty graph") {
            auto emptyGraph { AdjacencyList{} };
            
            auto emptyColoring { Coloring{} };
            CHECK(isProperVertexColoring(emptyColoring, emptyGraph) == true);
            
            auto wrongSize { Coloring{0} };
            CHECK(isProperVertexColoring(wrongSize, emptyGraph) == false);
        }
        
        SUBCASE("Single vertex") {
            auto singleVertex { AdjacencyList{{}} };
            
            auto properColoring { Coloring{0} };
            CHECK(isProperVertexColoring(properColoring, singleVertex) == true);
            
            auto wrongSize1 { Coloring{} };
            CHECK(isProperVertexColoring(wrongSize1, singleVertex) == false);
            
            auto wrongSize2 { Coloring{0, 1} };
            CHECK(isProperVertexColoring(wrongSize2, singleVertex) == false);
        }
        
        SUBCASE("Graph without edges") {
            auto noEdges { AdjacencyList{{}, {}, {}, {}} };
            
            auto sameColors { Coloring{2, 2, 2, 2} };
            CHECK(isProperVertexColoring(sameColors, noEdges) == true);
            
            auto differentColors { Coloring{0, 1, 2, 3} };
            CHECK(isProperVertexColoring(differentColors, noEdges) == true);
            
            auto wrongSize { Coloring{0, 1, 2} };
            CHECK(isProperVertexColoring(wrongSize, noEdges) == false);
        }
        
        SUBCASE("Path graph (3 vertices)") {
            auto path { AdjacencyList{{1}, {0, 2}, {1}} };
            
            auto proper2Colors { Coloring{0, 1, 0} };
            CHECK(isProperVertexColoring(proper2Colors, path) == true);
            
            auto proper3Colors { Coloring{0, 1, 2} };
            CHECK(isProperVertexColoring(proper3Colors, path) == true);
            
            auto improper1 { Coloring{0, 0, 1} };
            CHECK(isProperVertexColoring(improper1, path) == false);
            
            auto improper2 { Coloring{0, 1, 1} };
            CHECK(isProperVertexColoring(improper2, path) == false);
        
            auto allSame { Coloring{5, 5, 5} };
            CHECK(isProperVertexColoring(allSame, path) == false);
        }
        
        SUBCASE("Triangle graph (K3)") {
            auto triangle { AdjacencyList{{1, 2}, {0, 2}, {0, 1}} };
            
            auto proper3Colors { Coloring{0, 1, 2} };
            CHECK(isProperVertexColoring(proper3Colors, triangle) == true);

            auto improper1 { Coloring{0, 0, 1} };
            CHECK(isProperVertexColoring(improper1, triangle) == false);
            
            auto improper2 { Coloring{0, 1, 0} };
            CHECK(isProperVertexColoring(improper2, triangle) == false);
            
            auto improper3 { Coloring{1, 0, 1} };
            CHECK(isProperVertexColoring(improper3, triangle) == false);
            
            auto allSame { Coloring{3, 3, 3} };
            CHECK(isProperVertexColoring(allSame, triangle) == false);
        }
        
        SUBCASE("Complete graph K4") {
            auto k4 = AdjacencyList
            {
                {1, 2, 3},
                {0, 2, 3},
                {0, 1, 3},
                {0, 1, 2},
            };
            
            auto proper4Colors { Coloring{0, 1, 2, 3} };
            CHECK(isProperVertexColoring(proper4Colors, k4) == true);
            
            auto improper { Coloring{0, 1, 2, 2} };
            CHECK(isProperVertexColoring(improper, k4) == false);
            
            auto wrongSize { Coloring{0, 1, 2} };
            CHECK(isProperVertexColoring(wrongSize, k4) == false);
        }
    }
    
    TEST_CASE("randomColoring")
    {
        // TODO
    }

    TEST_CASE("computeVertexColoring")
    {
        SUBCASE("proper coloring  1")
        {
            auto graph = AdjacencyList
            {
                {1, 2},
                {0, 2},
                {0, 1, 3, 6},
                {2, 4, 5},
                {3, 5, 6},
                {3, 4},
                {2, 4}
            };

            auto forbidden     { ForbiddenColors(graph.size()) };
            auto startColoring { Coloring{1, 2, 1, 2, 1, 2, 2} };
            auto maxColor      { computeVertexColoring(graph, forbidden, startColoring) };
            
            CHECK(maxColor == 2);
            CHECK(isProperVertexColoring(startColoring, graph));
        }

        SUBCASE("proper coloring 2")
        {
            auto graph = AdjacencyList 
            {
                {1, 3},
                {0, 2},
                {1, 3},
                {0, 2},
            };

            auto forbidden     { ForbiddenColors(graph.size()) };
            auto startColoring { Coloring{ 1, 1, 1, 1 } };
            auto maxColor      { computeVertexColoring(graph, forbidden, startColoring) };

            CHECK(maxColor <= 2);
            CHECK(isProperVertexColoring(startColoring, graph));
        }

        SUBCASE("respects forbidden colors")
        {
            auto graph = AdjacencyList
            {
                {1, 2},
                {0, 2},
                {0, 1},
            };

            auto forbidden     { ForbiddenColors{{1}, {2}, {3}} };
            auto startColoring { Coloring{ 2, 3, 1 } };
            auto maxColor      { computeVertexColoring(graph, forbidden, startColoring) };

            CHECK(startColoring[0] != 1);
            CHECK(startColoring[1] != 2);
            CHECK(startColoring[2] != 3);
            CHECK(isProperVertexColoring(startColoring, graph));
        }

        SUBCASE("empty graph")
        {
            auto empty          { AdjacencyList{} };
            auto forbiddenEmpty { ForbiddenColors{} };
            auto coloring       { Coloring{} };

            auto maxColor { computeVertexColoring(empty, forbiddenEmpty, coloring) };

            CHECK(maxColor == 0);
            CHECK(coloring.empty());
        }

        SUBCASE("single vertex")
        {
            auto single          { AdjacencyList{{}} };
            auto forbiddenSingle { ForbiddenColors{{}} };
            auto coloring        { Coloring{1} };

            auto maxColor { computeVertexColoring(single, forbiddenSingle, coloring) };

            CHECK(maxColor == 1);
            CHECK(coloring[0] == 1);
        }

        SUBCASE("k3,3")
        {
            auto k33 = AdjacencyList
            {
                { 3, 4, 5 },
                { 3, 4, 5 },
                { 3, 4, 5 },
                { 0, 1, 2 },
                { 0, 1, 2 },
                { 0, 1, 2 },
            };

            auto forbidden { ForbiddenColors(k33.size()) };
            auto coloring  { Coloring(k33.size()) };

            auto maxColor { computeVertexColoring(k33, forbidden, coloring) };

            CHECK(maxColor == 1);
            CHECK(isProperVertexColoring(coloring, k33));
        }

        SUBCASE("k5")
        {
            auto k5 = AdjacencyList
            {
                { 1, 2, 3, 4 },
                { 0, 2, 3, 4 },
                { 0, 1, 3, 4 },
                { 0, 1, 2, 4 },
                { 0, 1, 2, 3 },
            };

            auto forbidden { ForbiddenColors(k5.size()) };
            auto coloring  { Coloring(k5.size()) };

            auto maxColor { computeVertexColoring(k5, forbidden, coloring) };

            CHECK(maxColor == 4);
            CHECK(isProperVertexColoring(coloring, k5));
        }

        SUBCASE("k4xk4")
        {
            auto k4xk4 = AdjacencyList
            {
                { 1, 2, 3, 4 },
                { 0, 2, 3, 5 },
                { 0, 1, 3, 6 },
                { 0, 1, 2, 7 },
                { 5, 6, 7, 0 },
                { 4, 6, 7, 1 },
                { 4, 5, 7, 2 },
                { 4, 5, 6, 3 },
            };

            auto forbidden { ForbiddenColors(k4xk4.size()) };
            auto coloring  { Coloring(k4xk4.size()) };

            auto maxColor { computeVertexColoring(k4xk4, forbidden, coloring) };

            CHECK(maxColor == 3);
            CHECK(isProperVertexColoring(coloring, k4xk4));
        }

    }

}
