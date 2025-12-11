/// @file  solve.cpp
#include "solve.hpp"
#include "solve_graph_adaptor.hpp"

namespace studies_schedule
{

    // Центральная функция приложения -- реализация алгоритма составления расписания на основе функций
    // из solve_graph_adaptor.hpp и graph_coloring.hpp.
    //
    // 1.  Построить граф предметов с помощью makeSubjectGraph(task.subjects).
    // 2.  Составить набор запрещённых цветов с помощью makeForbiddenColorsForSubjects(task).
    // 3.  Повторять:
    // 3.1 Найти правильную раскраску графа предметов (с учётом набора запрещённых цветов) с помощью computeVertexColoring.
    // 3.2 На основе раскраски из п.3.1 построить граф для назначения аудиторий с помощью makeSameColoredGraph.
    // 3.3 Найти правильную раскраску графа из п.3.2.
    // 3.4 Для раскраски из п.3.3 найти индексы предметов, на которых не хватило аудиторий,
    //     с помощью indicesOfImpossibleColors. Максимальный допустимый цвет = количество аудиторий - 1.
    // 3.5 Если в п.3.4 ничего не нашлось (функция вернула пустой вектор), то задача решена, покинуть цикл (п.4).
    // 3.6 Обновить запрещённые цвета с помощью updateForbiddenColorsForSubjectGraph.
    // 4.  Используя последние полученные в пп.3.1, 3.3 раскраски, построить набор назначений 
    //     с помощью функции makeAssignmentsFromColorings и вернуть его из функции.
    auto solve(Task const& task)
        -> Assignments
    {
        // TODO
        return {};
    }

    bool simpleSanityCheck(Task const& task, Assignments const& assignments)
    {
        // TODO
        return false;
    }

    auto findUnassignedSubjects(Task const& task, Assignments const& assignments)
        -> Subjects
    {
        // TODO
        return {};
    }

    bool isBetter(
            Assignments const& assigned, 
            Assignments const& thanAssigned,
            Task        const& accordingToTask
        )
    {
        return assigned.size() > thanAssigned.size(); // заглушка
    }

}
