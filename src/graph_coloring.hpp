/// @file  graph_coloring.hpp
/// @brief Алгоритм правильной вершинной раскраски графа.
#ifndef STUDIES_SCHEDULE_GRAPH_COLORING_HPP
#define STUDIES_SCHEDULE_GRAPH_COLORING_HPP

#include <cstdint>
#include <vector>

namespace studies_schedule
{

    /// @brief Номер вершины или цвета.
    using Index =
        std::int32_t;

    /// @brief Цвет задаётся номером с 0 до некоторого максимального (<= количеству вершин в графе).
    using Color =
        Index;

    /// @brief Раскраска (вершин: coloring[i] -- цвет i-й вершины).
    using Coloring =
        std::vector<Color>;

    /// @brief Номер вершины с 0 до (количество вершин - 1).
    using VertexIndex =
        Index;

    /// @brief Список соседей некой вершины: последовательность номеров вершин, являющихся соседними с данной.
    using Adjacency =
        std::vector<VertexIndex>;

    /// @brief Набор списков соседей: adjacencyList[i] содержит список соседей вершины i.
    using AdjacencyList =
        std::vector<Adjacency>;

    /// @brief Запрещённые цвета: forbiddenColors[i] содержит номера цветов, которые нельзя использовать для окрашивания вершины i.
    using ForbiddenColors =
        std::vector<std::vector<Color>>;

    /// @brief Проверить, является ли adjacencyList настоящим представлением графа (не содержит ли ошибок).
    ///
    /// - каждый список соседей содержит индексы вершин (числа из [0, size(adjacencyList) - 1]);
    /// - граф является неориентированным (сосед вершины i содержит i в своём списке соседей);
    /// - каждая вершина входит не более чем однажды в каждый список соседей (нет кратных рёбер);
    /// - никакая вершина не является соседом самой себя (нет петель).
    [[nodiscard]] bool isAdjacencyListValid(AdjacencyList const& adjacencyList);

    /// @brief Проверить, что вершинная раскраска не нарушает запретов на цвета.
    ///
    /// Для всех i: coloring[i] не встречается в наборе forbiddenColors[i].
    [[nodiscard]] bool colorsAreValid(Coloring const& coloring, ForbiddenColors const& forbiddenColors);

    /// @brief Проверить, что вершинная раскраска графа является правильной.
    ///
    /// Любые две вершины, которые являются соседями друг друга, окрашены в разные цвета.
    [[nodiscard]] bool isProperVertexColoring(Coloring const& coloring, AdjacencyList const& graph);

    /// @brief Создать случайную раскраску размера vertices в заданное число цветов colors.
    ///
    /// Заполнить случайно с равномерным распределением значениями [0, colors-1].
    [[nodiscard]] auto randomColoring(VertexIndex vertices, Color colors)
        -> Coloring;

    /// @brief                  Вычислить правильную вершинную раскраску графа.
    /// @param graph            входной граф, заданный списками соседей
    /// @param forbiddenColors  списки цветов, запрещённых для каждой вершины (индекс массива == индекс вершины)
    /// @param vertexColoring   вершинная раскраска (на входе -- произвольная, которую алгоритм пытается исправить)
    /// @return                 максимальный использованный цвет
    /// 
    /// Субоптимальный алгоритм полиномиальной временной сложности.
    auto computeVertexColoring(
            AdjacencyList   const& graph,
            ForbiddenColors const& forbiddenColors,
            Coloring&              vertexColoring
        ) -> Color;

}

#endif//STUDIES_SCHEDULE_GRAPH_COLORING_HPP
