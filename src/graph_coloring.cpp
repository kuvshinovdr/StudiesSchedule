/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"
#include <algorithm>

namespace studies_schedule
{

    bool isAdjacencyListValid(AdjacencyList const& adjacencyList)
    {
        // TODO
        return false;
    }

    bool colorsAreValid(Coloring const& coloring, ForbiddenColors const& forbiddenColors)
    {
        // coloring - вектор цветов по вершинам, forbiddenColors - вектор векторов запрещенных цветов для i-ой вершины.
        using namespace std;
        
        if (coloring.size() != forbiddenColors.size()) 
        return false;
        
        if (coloring.empty()) 
        return true;
        
        for (size_t i = 0; i < coloring.size(); ++i) 
        {
            Color color = coloring[i]; // как я понял тип данных int_32
            for (size_t j = 0; j < forbiddenColors[i].size(); ++j) 
            {
                if (color == forbiddenColors[i][j]) 
                return false;
            }
        }
        
        return true;
    }

    bool isProperVertexColoring(Coloring const& coloring, AdjacencyList const& graph)
    {
        // TODO
        return false;
    }

    auto randomColoring(VertexIndex vertices, Color colors)
        -> Coloring
    {
        // TODO
        return {};
    }

    auto computeVertexColoring(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring&              vertexColoring
        ) -> Color
    {
        auto maxColor = Color{-1};
        // TODO
        return maxColor;
    }

}
