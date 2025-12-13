/// @file  solve_graph_adaptor.cpp
#include "solve_graph_adaptor.hpp"
#include <algorithm>

namespace studies_schedule
{

    auto makeSubjectGraph(std::span<Subject const> subjects)
        -> AdjacencyList
    {
        const size_t n = subjects.size();
        AdjacencyList graph(n);
        
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                if (subjects[i].groupId == subjects[j].groupId ||
                    subjects[i].instructorName == subjects[j].instructorName) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        
        return graph;
    }

    auto makeForbiddenColorsForSubjects(Task const& task)
        -> ForbiddenColors
    {
        auto const& subjects = task.get<Subjects>();
        auto const& groups = task.get<Groups>();
        auto const& instructors = task.get<Instructors>();
        
        const size_t n = subjects.size();
        ForbiddenColors forbidden(n);
        
        for (size_t i = 0; i < n; ++i) {
            const Subject& subject = subjects[i];
            
            auto groupIndex = task.indexOf<Group>(subject.groupId);
            if (groupIndex.has_value()) {
                const Group& group = groups[groupIndex.value()];
                forbidden[i].insert(forbidden[i].end(), 
                                   group.forbidden.begin(), 
                                   group.forbidden.end());
            }
            
            auto instructorIndex = task.indexOf<Instructor>(subject.instructorName);
            if (instructorIndex.has_value()) {
                const Instructor& instructor = instructors[instructorIndex.value()];
                forbidden[i].insert(forbidden[i].end(),
                                   instructor.forbidden.begin(),
                                   instructor.forbidden.end());
            }
            
            std::sort(forbidden[i].begin(), forbidden[i].end());
            auto last = std::unique(forbidden[i].begin(), forbidden[i].end());
            forbidden[i].erase(last, forbidden[i].end());
        }
        
        return forbidden;
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

    auto makeAssignmentsFromColorings(
            Task     const& task,
            Coloring const& timeSlotsAssignment,
            Coloring const& roomAssignment
        ) -> Assignments
    {
        // TODO
        return {};
    }

}