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
            AdjacencyList emptyGraph = {};
            
            Coloring emptyColoring = {};
            CHECK(isProperVertexColoring(emptyColoring, emptyGraph) == true);
            
            Coloring wrongSize = {0};
            CHECK(isProperVertexColoring(wrongSize, emptyGraph) == false);
        }
        
        SUBCASE("Single vertex") {
            AdjacencyList singleVertex = {{}};
            
            Coloring properColoring = {0};
            CHECK(isProperVertexColoring(properColoring, singleVertex) == true);
            
            Coloring wrongSize1 = {};
            CHECK(isProperVertexColoring(wrongSize1, singleVertex) == false);
            
            Coloring wrongSize2 = {0, 1};
            CHECK(isProperVertexColoring(wrongSize2, singleVertex) == false);
        }
        
        SUBCASE("Graph without edges") {
            AdjacencyList noEdges = {{}, {}, {}, {}};
            
            Coloring sameColors = {2, 2, 2, 2};
            CHECK(isProperVertexColoring(sameColors, noEdges) == true);
            
            Coloring differentColors = {0, 1, 2, 3};
            CHECK(isProperVertexColoring(differentColors, noEdges) == true);
            
            Coloring wrongSize = {0, 1, 2};
            CHECK(isProperVertexColoring(wrongSize, noEdges) == false);
        }
        
        SUBCASE("Path graph (3 vertices)") {
            AdjacencyList path = {{1}, {0, 2}, {1}};
            
            Coloring proper2Colors = {0, 1, 0};
            CHECK(isProperVertexColoring(proper2Colors, path) == true);
            
            Coloring proper3Colors = {0, 1, 2};
            CHECK(isProperVertexColoring(proper3Colors, path) == true);
            
            Coloring improper1 = {0, 0, 1};
            CHECK(isProperVertexColoring(improper1, path) == false);
            
            Coloring improper2 = {0, 1, 1};
            CHECK(isProperVertexColoring(improper2, path) == false);
        
            Coloring allSame = {5, 5, 5};
            CHECK(isProperVertexColoring(allSame, path) == false);
        }
        
        SUBCASE("Triangle graph (K3)") {
            AdjacencyList triangle = {{1, 2}, {0, 2}, {0, 1}};
            
            Coloring proper3Colors = {0, 1, 2};
            CHECK(isProperVertexColoring(proper3Colors, triangle) == true);

            Coloring improper1 = {0, 0, 1}; 
            CHECK(isProperVertexColoring(improper1, triangle) == false);
            
            Coloring improper2 = {0, 1, 0};
            CHECK(isProperVertexColoring(improper2, triangle) == false);
            
            Coloring improper3 = {1, 0, 1};
            CHECK(isProperVertexColoring(improper3, triangle) == false);
            
            Coloring allSame = {3, 3, 3};
            CHECK(isProperVertexColoring(allSame, triangle) == false);
        }
        
        SUBCASE("Complete graph K4") {
            AdjacencyList k4 = {
                {1, 2, 3},
                {0, 2, 3},
                {0, 1, 3},
                {0, 1, 2}
            };
            
            Coloring proper4Colors = {0, 1, 2, 3};
            CHECK(isProperVertexColoring(proper4Colors, k4) == true);
            
            Coloring improper = {0, 1, 2, 2};  
            CHECK(isProperVertexColoring(improper, k4) == false);
            
            Coloring wrongSize = {0, 1, 2};
            CHECK(isProperVertexColoring(wrongSize, k4) == false);
        }
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
