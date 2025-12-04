/// @file  time_slots.hpp
/// @brief Общие определения в модели входных данных и модели результата (временные слоты).
#ifndef STUDIES_SCHEDULE_TIME_SLOTS_HPP
#define STUDIES_SCHEDULE_TIME_SLOTS_HPP

#include "string_operations_fwd.hpp"

#include <cstdint>
#include <vector>

namespace studies_schedule
{

    using TimeSlotIndex =
        std::int32_t;

    using TimeSlotIndices =
        std::vector<TimeSlotIndex>;

    struct TimeSlot
    {
        String dayOfWeek; // день недели
        String daySlot;   // номер в течении дня

        [[nodiscard]] constexpr auto operator<=>(TimeSlot const&) const noexcept = default;
    };

    using TimeSlots =
        std::vector<TimeSlot>;

}

#endif//STUDIES_SCHEDULE_TIME_SLOTS_HPP
