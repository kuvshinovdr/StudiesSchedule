/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"
#include <algorithm>
#include <set>

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

    auto randomColoring(VertexIndex vertices, Color colors)
        -> Coloring
    {
        // TODO
        return {};
    }

    auto listConflicts(
        AdjacencyList   const& graph,
        ForbiddenColors const& forbiddenColors,
        Coloring        const& vertexColoring
    ) -> Conflicts
    {
        Conflicts conflicts;
        for (Index vertex = 0; vertex < graph.size(); ++vertex)
        {
            std::vector<Index> neighborsColors = {};
            for (auto neighbor : graph[vertex])
            {
                neighborsColors.push_back(vertexColoring[neighbor]);
            }
            Index conflictRank = std::count(neighborsColors.begin(),
                                            neighborsColors.end(),
                                            vertexColoring[vertex]);
            if (conflictRank > 0)
            {

                std::set<Index> neighborsSet(neighborsColors.begin(), neighborsColors.end());

                neighborsSet.insert(forbiddenColors[vertex].begin(), forbiddenColors[vertex].end());
                Index newColor = *neighborsSet.rbegin() + 1;

                for (Index color = 0; color < newColor - 1; ++color)
                {
                    if (auto search = neighborsSet.find(color); search == neighborsSet.end())
                    {
                        newColor = color;
                        break;
                    }
                }

                ConflictData conflict = { conflictRank, newColor, vertex };
                conflicts.push_back(conflict);
            }
        }
        std::sort(conflicts.begin(), conflicts.end(),
            [](auto const& a, auto const& b) {
                return a.rank > b.rank;
            });
        return conflicts;
    }

    auto computeVertexColoring(
        AdjacencyList   const& graph,
        ForbiddenColors const& forbiddenColors,
        Coloring& vertexColoring
    ) -> Color
    {
        Color maxColor = 0;

        while (true)
        {
            auto conflicts = listConflicts(graph, forbiddenColors, vertexColoring);
            if (conflicts.empty())
            {
                for (auto c : vertexColoring)
                    maxColor = maxColor > c ? maxColor : c;
                return maxColor != 0 ? maxColor : graph.size();
            }

            std::set<Index> closed{};
            for (auto v : conflicts)
            {
                auto u = v.vertex;
                if (closed.find(u) != closed.end())
                {
                    continue;
                }
                vertexColoring[u] = v.color;
                for (auto ng : graph[u])
                {
                    closed.insert(ng);
                }
            }
        }
        return maxColor;
    }
}
