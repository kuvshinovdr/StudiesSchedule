/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"
#include <algorithm>
#include <ranges>

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
        if (coloring.size() != forbiddenColors.size()) {
            return false;
        }
        
        for (auto const& [forbidden, color]: std::views::zip(forbiddenColors, coloring)) {
            if (std::ranges::contains(forbidden, color)) {
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
