/// @file  assignments.hpp
/// @brief Назначения -- расписание в том виде, в котором оно получается в алгоритме.
#ifndef STUDIES_SCHEDULE_ASSIGNMENTS_HPP
#define STUDIES_SCHEDULE_ASSIGNMENTS_HPP

#include "time_slots.hpp"

namespace studies_schedule
{

    using Index =
        std::ptrdiff_t;

    using RoomIndex         = Index;
    using GroupIndex        = Index;
    using InstructorIndex   = Index;
    using SubjectIndex      = Index;

    struct Assignment
    {
        TimeSlotIndex   timeSlot    {-1};
        RoomIndex       room        {-1};
        GroupIndex      group       {-1};
        InstructorIndex instructor  {-1};
        SubjectIndex    subject     {-1};
    };

    using Assignments =
        std::vector<Assignment>;


}

#endif//STUDIES_SCHEDULE_ASSIGNMENTS_HPP
