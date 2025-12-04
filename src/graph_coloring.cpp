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
        Coloring& vertexColoring
    ) -> std::vector<std::vector<Index>>
    {
        std::vector<std::vector<Index>> conflicts;
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

                for (Index color = 1; color < newColor - 1; ++color)
                {
                    if (auto search = neighborsSet.find(color); search == neighborsSet.end())
                    {
                        newColor = color;
                        break;
                    }
                }

                std::vector<Index> conflict = { conflictRank, newColor, vertex };
                conflicts.push_back(conflict);
            }
        }
        std::sort(conflicts.begin(), conflicts.end(),
            [](const std::vector<Index>& a, const std::vector<Index>& b) {
                return a[0] > b[0];
            });
        // оставила только сортировку по убыванию количества конфликтов
        return conflicts;

    }

    auto computeVertexColoring(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring&              vertexColoring
        ) -> Color
    {
        auto maxColor = Color{-1};
        
        // if (ForbiddenColors.size() != graph.size())
        
                 


        return maxColor;
    }

}
