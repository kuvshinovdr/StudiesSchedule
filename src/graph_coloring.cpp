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

    auto listConflicts(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring        const& vertexColoring
        ) -> Conflicts
    {
        Conflicts conflicts;
        for (VertexIndex vertex = 0; vertex < graph.size(); ++vertex)
        {
            std::vector<VertexIndex> neighborsColors = {};
            for (auto neighbor : graph[vertex])
            {
                neighborsColors.push_back(vertexColoring[neighbor]);
            }
            VertexIndex conflictRank = std::count(neighborsColors.begin(),
                                            neighborsColors.end(),
                                            vertexColoring[vertex]);
            if (conflictRank > 0)
            {

                std::set<VertexIndex> neighborsSet(neighborsColors.begin(), neighborsColors.end());

                neighborsSet.insert(forbiddenColors[vertex].begin(), forbiddenColors[vertex].end());
                VertexIndex newColor = *neighborsSet.rbegin() + 1;

                for (VertexIndex color = 0; color < newColor - 1; ++color)
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

            std::set<VertexIndex> closed{};
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
