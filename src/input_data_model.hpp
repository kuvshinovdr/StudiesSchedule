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

    struct Group
    {
        String          id          {};
        TimeSlotIndices forbidden   {};
    };

    struct Instructor
    {
        String          name        {};
        TimeSlotIndices forbidden   {};
    };

    struct TimeSlot
    {
        String dayOfWeek; // день недели
        String daySlot;   // номер в течении дня
    };

    struct Subject
    {
        String title;
        String groupId;
        String instructorName;
    };

}

#endif//STUDIES_SCHEDULE_INPUT_DATA_MODEL_HPP
