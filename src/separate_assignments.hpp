/// @file  separate_assignments.hpp
/// @brief Разделение назначений на назначенные (имеющие позицию на неделе) и неназначенные.
#ifndef STUDIES_SCHEDULE_SEPARATE_ASSIGNMENTS_HPP
#define STUDIES_SCHEDULE_SEPARATE_ASSIGNMENTS_HPP

#include "assignments.hpp"

namespace studies_schedule
{

    /// @brief Разделение назначений на те, на которых хватило времени в неделе (assigned), и те, на которых не хватило (unassigned).
    struct SeparateAssignments
    {
        Assignments     assigned    {};
        Assignments     unassigned  {};

        [[nodiscard]] constexpr auto operator<=>(SeparateAssignments const&) const noexcept = default;
    };

    /// @brief                    Разделить назначения на группы "назначенных" и "не назначенных".
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

}

#endif//STUDIES_SCHEDULE_SEPARATE_ASSIGNMENTS_HPP
