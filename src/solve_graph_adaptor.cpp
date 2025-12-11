/// @file  solve_graph_adaptor.cpp
#include "solve_graph_adaptor.hpp"

namespace studies_schedule
{

    auto makeSubjectGraph(Subjects const& subjects)
        -> AdjacencyList
    {
        // TODO
        return {};
    }

    auto makeForbiddenColorsForSubjects(Task const& task)
        -> ForbiddenColors
    {
        // TODO
        return {};
    }

    auto makeSameColoredGraph(Coloring const& coloring)
        -> AdjacencyList
    {
        // TODO
        return {};
    }

    auto indicesOfImpossibleColors(
            Coloring const& coloring,
            Color           maxPossibleColor
        ) -> IndicesOfImpossibleColors
    {
        // TODO
        return {};
    }

    void updateForbiddenColorsForSubjectGraph(
            ForbiddenColors&                 forbiddenColorsToModify,
            Coloring                  const& subjectTimeSlots,
            IndicesOfImpossibleColors const& subjectsToMove
        )
    {
        // TODO
    }

}
