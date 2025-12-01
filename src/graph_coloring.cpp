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
        // TODO
        return false;
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
