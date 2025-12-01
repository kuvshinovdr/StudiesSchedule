/// @file  output.hpp
/// @brief Формирование файлов результатов.
#ifndef STUDIES_SCHEDULE_OUTPUT_HPP
#define STUDIES_SCHEDULE_OUTPUT_HPP

#include "assignments.hpp"
#include "schedule.hpp"

namespace studies_schedule
{

    struct SeparateAssignments
    {
        Assignments     assigned    {};
        Assignments     unassigned  {};
    };

    [[nodiscard]] auto separateAssignments(
            Assignments&& assignments, 
            TimeSlotIndex availableTimeSlots
        ) -> SeparateAssignments;

    [[nodiscard]] auto makeGroupSchedule(Assignments const&)
        -> GroupSchedule;

    [[nodiscard]] auto makeInstructorSchedule(Assignments const&)
        -> InstructorSchedule;

    [[nodiscard]] auto makeRoomSchedule(Assignments const&)
        -> RoomSchedule;

}

#endif//STUDIES_SCHEDULE_OUTPUT_HPP
