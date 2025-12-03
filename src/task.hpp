/// @file  task.hpp
/// @brief Структуры данных, описывающие входные данные задачи составления расписания (т.е. постановку задачи).
#ifndef STUDIES_SCHEDULE_TASK_HPP
#define STUDIES_SCHEDULE_TASK_HPP

#include "time_slots.hpp"

namespace studies_schedule
{

    struct Room
    {
        String          id          {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Room const&) const noexcept = default;
    };

    using Rooms =
        std::vector<Room>;

    struct Group
    {
        String          id          {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Group const&) const noexcept = default;
    };

    using Groups =
        std::vector<Group>;

    struct Instructor
    {
        String          name        {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Instructor const&) const noexcept = default;
    };

    using Instructors =
        std::vector<Instructor>;

    struct Subject
    {
        String title            {};
        String groupId          {};
        String instructorName   {};

        [[nodiscard]] constexpr auto operator<=>(Subject const&) const noexcept = default;
    };

    using Subjects =
        std::vector<Subject>;

    struct Task
    {
        TimeSlots   timeSlots   {};
        Rooms       rooms       {};
        Groups      groups      {};
        Instructors instructors {};
        Subjects    subjects    {};

        [[nodiscard]] constexpr auto operator<=>(Task const&) const noexcept = default;
    };

}

#endif//STUDIES_SCHEDULE_TASK_HPP
