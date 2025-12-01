/// @file  input_data_model.hpp
/// @brief Структуры данных, описывающие входные данные задачи составления расписания.
#ifndef STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP
#define STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP

#include "time_slots.hpp"

namespace studies_schedule
{

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
