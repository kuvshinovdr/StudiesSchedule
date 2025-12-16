/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"

namespace studies_schedule
{

    bool isAdjacencyListValid(AdjacencyList const& adjacencyList)
    {
        // TODO
        return false;
    }

    bool colorsAreValid(Coloring const& coloring, ForbiddenColors const& forbiddenColors)
    {
        // TODO
        return false;
    }

   bool isProperVertexColoring(Coloring const& coloring, AdjacencyList const& graph)
{
    if (coloring.size() != graph.size())
    {
        return false;
    }
    
    for (size_t vertex = 0; vertex < graph.size(); ++vertex)
    {
        Color currentColor = coloring[vertex];
        
        for (VertexIndex neighbor : graph[vertex])
        {
            if (neighbor < 0 || neighbor >= static_cast<VertexIndex>(graph.size()))
            {
                return false;
            }
            
            if (coloring[neighbor] == currentColor)
            {
                return false;
            }
        }
    }
    
    return true;
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
