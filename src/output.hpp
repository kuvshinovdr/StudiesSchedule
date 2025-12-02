/// @file  output.hpp
/// @brief Формирование файлов результатов.
#ifndef STUDIES_SCHEDULE_OUTPUT_HPP
#define STUDIES_SCHEDULE_OUTPUT_HPP

#include "assignments.hpp"
#include "schedule.hpp"

namespace studies_schedule
{

    /// @brief Разделение назначений на те, на которых хватило времени в неделе (assigned), и те, на которых не хватило (unassigned).
    struct SeparateAssignments
    {
        Assignments     assigned    {};
        Assignments     unassigned  {};
    };

    /// @brief                    Разделить назначения на группы "назначенных" и "неназначенных".
    /// @param allAssignments     исходный набор назначений
    /// @param availableTimeSlots доступное число временных слотов
    /// @return                   два набора назначений (поля assigned и unassigned)
    /// 
    /// В assigned попадают назначения, временные слоты timeSlot которых попадают в промежуток
    /// [0, availableTimeSlots-1]. Все остальные назначения попадают в unassigned.
    [[nodiscard]] auto separateAssignments(
            Assignments const&      allAssignments, 
            TimeSlotIndex           availableTimeSlots
        ) -> SeparateAssignments;

    /// @brief  Построить расписание групп по набору назначений.
    [[nodiscard]] auto makeGroupSchedule(Assignments const&)
        -> GroupSchedule;

    /// @brief  Построить расписание преподавателей по набору назначений.
    [[nodiscard]] auto makeInstructorSchedule(Assignments const&)
        -> InstructorSchedule;

    /// @brief  Построить расписание аудиторий по набору назначений.
    [[nodiscard]] auto makeRoomSchedule(Assignments const&)
        -> RoomSchedule;

}

#endif//STUDIES_SCHEDULE_OUTPUT_HPP
