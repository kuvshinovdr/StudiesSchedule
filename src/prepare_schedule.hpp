/// @file  prepare_schedule.hpp
/// @brief Формирование подготовленных к записи в таблицы расписаний на основе списка назначений.
#ifndef STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP
#define STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP

#include "assignments.hpp"
#include "schedule.hpp"
#include "task.hpp"

namespace studies_schedule
{

    /// @brief  Построить расписание группы с заданным индексом по набору назначений.
    [[nodiscard]] auto makeGroupSchedule(GroupIndex groupIndex, Assignments const&, Task const&)
        -> GroupSchedule;

    /// @brief  Построить расписание преподавателя с заданным индексом по набору назначений.
    [[nodiscard]] auto makeInstructorSchedule(InstructorIndex instructorIndex, Assignments const&, Task const&)
        -> InstructorSchedule;

    /// @brief  Построить расписание аудитории с заданным индексом по набору назначений.
    [[nodiscard]] auto makeRoomSchedule(RoomIndex roomIndex, Assignments const&, Task const&)
        -> RoomSchedule;

}

#endif//STUDIES_SCHEDULE_PREPARE_SCHEDULE_HPP
