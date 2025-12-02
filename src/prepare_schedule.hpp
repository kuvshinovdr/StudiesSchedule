/// @file  prepare_schedule.hpp
/// @brief Формирование подготовленных к записи в таблицы расписаний на основе списка назначений.
#ifndef STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP
#define STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP

#include "assignments.hpp"
#include "schedule.hpp"
#include "task.hpp"

namespace studies_schedule
{

    /// @brief  Построить расписание групп по набору назначений.
    [[nodiscard]] auto makeGroupSchedule(Assignments const&, Task const&)
        -> GroupSchedule;

    /// @brief  Построить расписание преподавателей по набору назначений.
    [[nodiscard]] auto makeInstructorSchedule(Assignments const&, Task const&)
        -> InstructorSchedule;

    /// @brief  Построить расписание аудиторий по набору назначений.
    [[nodiscard]] auto makeRoomSchedule(Assignments const&, Task const&)
        -> RoomSchedule;

}

#endif//STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP
