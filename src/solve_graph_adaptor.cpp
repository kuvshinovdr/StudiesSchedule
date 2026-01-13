#include "solve_graph_adaptor.hpp"

#include <algorithm>
#include <unordered_map>

namespace studies_schedule

{

auto makeSameColoredGraph(Coloring const& coloring)
    -> AdjacencyList
{
    const std::size_t n = coloring.size();
    AdjacencyList graph(n);

    std::unordered_map<Color, std::vector<VertexIndex>> byColor;

    for (VertexIndex i = 0; i < n; ++i)
        byColor[coloring[i]].push_back(i);

    // соединяем вершины одинакового цвета
    for (auto const& [color, vertices] : byColor)
    {
        for (std::size_t i = 0; i < vertices.size(); ++i)
        {
            for (std::size_t j = i + 1; j < vertices.size(); ++j)
            {
                graph[vertices[i]].push_back(vertices[j]);
                graph[vertices[j]].push_back(vertices[i]);
            }
        }
    }

    return graph;
}

auto indicesOfImpossibleColors(
        Coloring const& coloring,
        Color           maxPossibleColor
    ) -> IndicesOfImpossibleColors
{
    IndicesOfImpossibleColors result;

    for (VertexIndex i = 0; i < coloring.size(); ++i)
    {
        if (coloring[i] > maxPossibleColor)
            result.push_back(i);
    }
    return result;
}

void updateForbiddenColorsForSubjectGraph(
        ForbiddenColors&                 forbiddenColorsToModify,
        Coloring                  const& subjectTimeSlots,
        IndicesOfImpossibleColors const& subjectsToMove
    )
{
    for (VertexIndex i : subjectsToMove)
    {
        Color color = subjectTimeSlots[i];
        auto& forbidden = forbiddenColorsToModify[i];

        if (std::find(forbidden.begin(), forbidden.end(), color)
            == forbidden.end())
        {
            forbidden.push_back(color);
        }
    }
}

}