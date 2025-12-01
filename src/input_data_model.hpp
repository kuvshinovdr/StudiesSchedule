/// @file  input_data_model.hpp
/// @brief Структуры данных, описывающие входные данные задачи составления расписания.
#ifndef STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP
#define STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP

#include "string_operations_fwd.hpp"
#include <vector>

namespace studies_schedule
{

    using TimeSlotIndex =
        std::ptrdiff_t;

    using TimeSlotIndices =
        std::vector<TimeSlotIndex>;

    struct Room
    {
        String          id          {};
        TimeSlotIndices forbidden   {};
    };

    using Rooms =
        std::vector<Room>;

    struct Group
    {
        String          id          {};
        TimeSlotIndices forbidden   {};
    };

    using Groups =
        std::vector<Group>;

    struct Instructor
    {
        String          name        {};
        TimeSlotIndices forbidden   {};
    };

    using Instructors =
        std::vector<Instructor>;

    struct TimeSlot
    {
        String dayOfWeek; // день недели
        String daySlot;   // номер в течении дня
    };

    using TimeSlots =
        std::vector<TimeSlot>;

    struct Subject
    {
        String title;
        String groupId;
        String instructorName;
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
    };

}

#endif//STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP
