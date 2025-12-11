/// @file  solve.cpp
#include "solve.hpp"
#include "solve_graph_adaptor.hpp"

namespace studies_schedule
{

    // Центральная функция приложения -- реализация алгоритма составления расписания на основе функций
    // из solve_graph_adaptor.hpp и graph_coloring.hpp.
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
