/// @file  output_data_model.hpp
/// @brief Структуры данных, описывающие результаты составления расписания.
#ifndef STUDIES_SCHEDULE_OUTPUT_DATA_MODEL_HPP
#define STUDIES_SCHEDULE_OUTPUT_DATA_MODEL_HPP

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

    struct Schedule
    {
        TimeSlots           timeSlots           {};
        GroupSchedule       groupSchedule       {};
        InstructorSchedule  instructorSchedule  {};
        RoomSchedule        roomSchedule        {};
    };

}

#endif//STUDIES_SCHEDULE_OUTPUT_DATA_MODEL_HPP
