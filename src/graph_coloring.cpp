/// @file  graph_coloring.cpp
#include "graph_coloring.hpp"
#include <algorithm>
#include <ranges>

#include <limits>
#include <tuple>
#include <functional>
#include <algorithm>
#include <ranges>

namespace studies_schedule
{

    [[nodiscard]] static constexpr auto adaptPair(auto takesPair)
    {
        return [takesPair](auto&& pair)
        {
            auto&& [a, b] = pair;
            return takesPair(a, b);
        };
    }

    [[nodiscard]] static constexpr bool adjacencyHasIndicesOutOfRange(VertexIndex upperBound, Adjacency const& adj)
    {
        return std::ranges::any_of(adj, [upperBound](VertexIndex v) { return upperBound <= v || v < 0; });
    }

    [[nodiscard]] static constexpr bool adjacencyHasLoops(std::size_t inVertex, Adjacency const& adj)
    {
        return std::ranges::contains(adj, static_cast<VertexIndex>(inVertex));
    }

    [[nodiscard]] static bool adjacencyHasRepeats(Adjacency const& adj)
    {
        auto sortedCopy = adj;
        std::ranges::sort(sortedCopy);
        return std::ranges::adjacent_find(sortedCopy) != sortedCopy.end();
    }

    bool isAdjacencyListValid(AdjacencyList const& adjacencyList)
    {
        // Возможные проверки:
        // 0. Принципиальный размер списка.
        if (static_cast<std::size_t>(std::numeric_limits<VertexIndex>::max()) < adjacencyList.size()) {
            return false;
        }

        // 1. Отсутствие индексов за пределами размера массива.
        if (std::ranges::any_of(adjacencyList,
                                std::bind_front(adjacencyHasIndicesOutOfRange, static_cast<VertexIndex>(adjacencyList.size())))) {
            return false;
        }

        // 2a. Отсутствие петель
        if (std::ranges::any_of(std::views::enumerate(adjacencyList), adaptPair(adjacencyHasLoops))) {
            return false;
        }

        // 2b. Отсутствие кратных рёбер (повторов индексов).
        if (std::ranges::any_of(adjacencyList, adjacencyHasRepeats)) {
            return false;
        }

        // 3. Неориентированность графа: если j принадлежит adjacencyList[i], то i принадлежит adjacencyList[j].
        for (auto i = std::size_t{0}; i < adjacencyList.size(); ++i) {
            auto const u = static_cast<VertexIndex>(i);
            for (auto v: adjacencyList[i]) {
                if (u < v && !std::ranges::contains(adjacencyList[v], u)) {
                    return false;
                }
            }
        }

        return true;
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

    bool listConflicts(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring        const& vertexColoring,
            Coloring&              neighborColors,
            Conflicts&             conflicts
        )
    {
        conflicts.clear();

        for (auto vertex = 0zu; vertex < graph.size(); ++vertex) {
            neighborColors.assign_range(
                std::views::transform(graph[vertex], mapArray(vertexColoring)));
            
            auto const conflictRank 
            { 
                std::ranges::count(neighborColors, vertexColoring[vertex])
            };
            
            if (conflictRank == 0) {
                continue;
            }

            neighborColors.insert_range(neighborColors.end(), forbiddenColors[vertex]);
            
            std::ranges::sort(neighborColors);
            neighborColors.erase(
                std::unique(neighborColors.begin(), neighborColors.end()), 
                neighborColors.end());

            auto const newColor
            { 
                *std::ranges::mismatch(std::views::iota(Color{}), neighborColors).in1
            };

            conflicts.emplace_back(ConflictData
                { 
                    .rank   = static_cast<VertexIndex>(conflictRank),
                    .color  = newColor, 
                    .vertex = static_cast<VertexIndex>(vertex)
                });
        }

        std::ranges::sort(conflicts,
            [](auto const& a, auto const& b)
            {
                return a.rank > b.rank;
            });

        return !conflicts.empty();
    }

    auto listConflicts(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring        const& vertexColoring
        ) -> Conflicts
    {
        auto neighborColors { Coloring{}  };
        auto conflicts      { Conflicts{} };
        listConflicts(graph, forbiddenColors, vertexColoring, neighborColors, conflicts);
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

        auto closed         { std::vector<bool>{} };
        auto neighborColors { Coloring{}  };
        auto conflicts      { Conflicts{} };
        
        neighborColors.reserve(32);
        conflicts.reserve(graph.size());

        while (listConflicts(graph, forbiddenColors, vertexColoring, neighborColors, conflicts)) {
            closed.assign(graph.size(), false);
            for (auto conflict : conflicts) {
                if (auto const u { conflict.vertex }; !closed[u]) {
                    vertexColoring[u] = conflict.color;
                    for (auto neighbor : graph[u]) {
                        closed[neighbor] = true;
                    }
                }
            }
        }

        return std::ranges::max(vertexColoring);
    }
}
