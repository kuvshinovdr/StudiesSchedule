/// @file  schedule.hpp
/// @brief Расписание, представленное в виде трёх таблиц.
#ifndef STUDIES_SCHEDULE_SCHEDULE_HPP
#define STUDIES_SCHEDULE_SCHEDULE_HPP

#include "time_slots.hpp"

namespace studies_schedule
{

    struct GroupScheduleRow
    {
        String room;
        String subject;
        String instructor;
    };

    using GroupSchedule =
        std::vector<GroupScheduleRow>;

    struct InstructorScheduleRow
    {
        String room;
        String subject;
        String group;
    };

    using InstructorSchedule =
        std::vector<InstructorScheduleRow>;

    struct RoomScheduleRow
    {
        String subject;
        String group;
        String instructor;
    };

    using RoomSchedule =
        std::vector<RoomScheduleRow>;

}

#endif//STUDIES_SCHEDULE_SCHEDULE_HPP
