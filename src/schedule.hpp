/// @file  schedule.hpp
/// @brief Расписание, представленное в виде трёх таблиц.
#ifndef STUDIES_SCHEDULE_SCHEDULE_HPP
#define STUDIES_SCHEDULE_SCHEDULE_HPP

#include "time_slots.hpp"

namespace studies_schedule
{

    struct GroupScheduleRow
    {
        TimeSlot timeSlot;

        String room;
        String subject;
        String instructor;

        [[nodiscard]] constexpr auto operator<=>(GroupScheduleRow const&) const noexcept = default;
    };

    using GroupSchedule =
        std::vector<GroupScheduleRow>;

    struct InstructorScheduleRow
    {
        TimeSlot timeSlot;

        String room;
        String subject;
        String group;

        [[nodiscard]] constexpr auto operator<=>(InstructorScheduleRow const&) const noexcept = default;
    };

    using InstructorSchedule =
        std::vector<InstructorScheduleRow>;

    struct RoomScheduleRow
    {
        TimeSlot timeSlot;

        String subject;
        String group;
        String instructor;

        [[nodiscard]] constexpr auto operator<=>(RoomScheduleRow const&) const noexcept = default;
    };

    using RoomSchedule =
        std::vector<RoomScheduleRow>;

}

#endif//STUDIES_SCHEDULE_SCHEDULE_HPP
