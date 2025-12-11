/// @file  solve_graph_adaptor.hpp
/// @brief Связка задач составления расписания в виде набора назначений и задачи правильной раскраски графа.
#ifndef STUDIES_SCHEDULE_SOLVE_GRAPH_ADAPTOR_HPP
#define STUDIES_SCHEDULE_SOLVE_GRAPH_ADAPTOR_HPP

#include "task.hpp"
#include "graph_coloring.hpp"

namespace studies_schedule
{

    /// @brief      Составить граф, вершины которого соответствуют тройкам группа-преподаватель-предмет.
    /// @param task постановка задачи, задающая тройки (см. subjects)
    /// @return     списки соседей, задающие граф
    /// 
    /// Подготовка для решения задачи 1 (см. README).
    [[nodiscard]] auto makeSubjectGraph(Subjects const& subjects)
        -> AdjacencyList;

    /// @brief      Построить построить наборы запрещённых временных слотов.
    /// @param task постановка задачи (см. поля forbidden)
    /// @return     списки запрещённых цветов для предметов
    /// 
    /// Номер временного слота равен номеру цвета в задаче 1, 
    /// так что это запрещённые цвета.
    /// Цвет запрещён для предмета, если он запрещён для преподавателя или для группы,
    /// которым назначен предмет.
    [[nodiscard]] auto makeForbiddenColorsForSubjects(Task const& task)
        -> ForbiddenColors;

    /// @brief          Построить граф, соединяя вершины, окрашенные одинаково.
    /// @param coloring исходная раскраска (заодно задаёт число вершин графа)
    /// @return         списки соседей, задающие граф
    /// 
    /// Подготовка для решения задачи 2 (см. README).
    /// Исходная раскраска получается при решении задачи 1.
    [[nodiscard]] auto makeSameColoredGraph(Coloring const& coloring)
        -> AdjacencyList;
    
    using IndicesOfImpossibleColors =
        std::vector<VertexIndex>;

    /// @brief                  Найти индексы всех вершин графа, окрашенных в недоступные цвета.
    /// @param coloring         вершинная раскраска графа
    /// @param maxPossibleColor максимальный доступный цвет
    /// @return                 массив индексов вершин
    /// 
    /// Пройти по coloring, сохранить индексы всех элементов > maxPossibleColor.
    [[nodiscard]] auto indicesOfImpossibleColors(
            Coloring const& coloring, 
            Color           maxPossibleColor
        ) -> IndicesOfImpossibleColors;

    /// @brief Запретить цвет(а) предмету(предметам), не вписавшимся в аудитории.
    /// @param forbiddenColorsToModify запрещённые цвета (временные слоты) в задаче раскраски графа предметов (задача 1)
    /// @param subjectTimeSlots        предыдущий результат раскраски графа предметов (решение задачи 1)
    /// @param subjectsToMove          набор предметов, не вписавшихся в аудитории во временных слотах, назначенных для этих предметов
    /// 
    /// ...
    void updateForbiddenColorsForSubjectGraph(
            ForbiddenColors&                 forbiddenColorsToModify,
            Coloring                  const& subjectTimeSlots,
            IndicesOfImpossibleColors const& subjectsToMove
        );

}

#endif//STUDIES_SCHEDULE_SOLVE_GRAPH_ADAPTOR_HPP
