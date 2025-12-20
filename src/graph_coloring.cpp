/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"

#include <tuple>
#include <functional>
#include <algorithm>
#include <ranges>
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

    // Чего-то подобного не хватает в стандартной библиотеке.
    [[nodiscard]] constexpr auto mapArray(auto const& array)
    {
        return [&](auto const& index) -> decltype(auto)
            {
                return array[index];
            };
    }

    // Это тоже должно было бы быть в стандартной библиотеке или даже частью языка.
    [[nodiscard]] constexpr auto applyTuple(auto&& fun)
    {
        return [&](auto&& tuple) -> decltype(auto)
            {
                return std::apply(fun, tuple);
            };
    }

    [[nodiscard]] bool adjacencyContainsColor(
            Coloring  const& coloring, 
            Adjacency const& adjacency, 
            Color            color
        )
    {
        return std::ranges::contains(std::views::transform(adjacency, mapArray(coloring)), color);
    }

    bool isProperVertexColoring(Coloring const& coloring, AdjacencyList const& graph)
    {
        auto checkColor { applyTuple(std::bind_front(adjacencyContainsColor, std::cref(coloring))) };
        return coloring.size() == graph.size() && 
            std::ranges::none_of(std::views::zip(graph, coloring), checkColor);
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
        auto conflicts { Conflicts{} };
        
        for (auto vertex = 0zu; vertex < graph.size(); ++vertex) {
            auto neighborsColors { Coloring{} };
            
            for (auto neighbor : graph[vertex]) {
                neighborsColors.push_back(vertexColoring[neighbor]);
            }

            auto const conflictRank { std::ranges::count(neighborsColors, vertexColoring[vertex]) };
            
            if (conflictRank == 0) {
                continue;
            }

            auto neighborsSet { std::set(std::from_range, neighborsColors) };

            neighborsSet.insert_range(forbiddenColors[vertex]);
            
            auto newColor { *neighborsSet.rbegin() + 1 };

            for (VertexIndex color = 0; color < newColor - 1; ++color) {
                if (!neighborsSet.contains(color)) {
                    newColor = color;
                    break;    
                }
            }

            conflicts.emplace_back(ConflictData
                { 
                    .rank   = static_cast<VertexIndex>(conflictRank),
                    .color  = newColor, 
                    .vertex = static_cast<VertexIndex>(vertex)
                });
        }

        std::ranges::sort(conflicts,
            [](auto const& a, auto const& b) {
                return a.rank > b.rank;
            });

        return conflicts;
    }

    auto computeVertexColoring(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring&              vertexColoring
        ) -> Color
    {
        if (vertexColoring.size() != graph.size()) {
            vertexColoring.resize(graph.size());
        }

        if (graph.empty()) {
            return 0;
        }

        for (auto maxColor = std::ranges::max(vertexColoring);;) {
            auto conflicts { listConflicts(graph, forbiddenColors, vertexColoring) };
            
            if (conflicts.empty()) {
                return maxColor;
            }

            auto closed { std::set<VertexIndex>{} };
            
            for (auto conflict : conflicts) {
                auto const u { conflict.vertex };
                if (closed.contains(u)) {
                    continue;
                }

                vertexColoring[u] = conflict.color;
                maxColor = std::max(conflict.color, maxColor);

                for (auto neighbor : graph[u]) {
                    closed.insert(neighbor);
                }
            }
        }
    }
}
