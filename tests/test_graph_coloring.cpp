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
            Coloring coloring               = {1, 3, 2, 4};
            ForbiddenColors forbiddenColors = {{2,4}, {1,2}, {4,3}, {1,2,3}};
            
            bool result = colorsAreValid(coloring, forbiddenColors);
            
            if (result == true)
            std::cout << "Успех\n";
            else 
            std::cout << "ОШИБКА!ОШИБКА!ОШИБКА!\n";
        }
        
        {
            Coloring coloring               = {5, 6, 7, 8};
            ForbiddenColors forbiddenColors = {{6,7}, {7,8}, {6,8}, {6,7,8}};
            
            bool result = colorsAreValid(coloring, forbiddenColors);
            
            if (result == false)
            std::cout << "Успех\n";
            else 
            std::cout << "ОШИБКА!ОШИБКА!ОШИБКА!\n";
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
