/// @file  input.cpp
#include "input.hpp"
#include "file_to_string.hpp"
#include "csv.hpp"
#include "log.hpp"

#include <ranges>
#include <algorithm>

namespace studies_schedule
{

    template <typename Result, typename RowTransform>
    [[nodiscard]] static auto readCsvData(String const& filename, RowTransform rowTransform)
        -> Expected<Result>
    {
        return 
            fileToString(filename)
            .and_then(parseCsv)
            .transform([rowTransform](Table&& table)
                {
                    return std::move(table) | std::views::transform(rowTransform) | std::ranges::to<Result>();
                });
    }

    auto readRooms(String const& filename)
        -> Expected<Rooms>
    {
        return readCsvData<Rooms>(filename, [](TableRow& row)
            {
                return !row.empty()? Room { .id = std::move(row[0]) }: Room{};
            });
    }

    auto readInstructors(String const& filename)
        -> Expected<Instructors>
    {
        // TODO
        return Instructors{};
    }

    auto readGroups(String const& filename)
        -> Expected<Groups>
    {
        // TODO
        return Groups{};
    }

    auto readSubjects(String const& filename)
        -> Expected<Subjects>
    {
        // TODO
        return Subjects{};
    }

    auto readTimeSlots(String const& filename)
        -> Expected<TimeSlots>
    {
        // TODO
        return TimeSlots{};
    }

    auto readForbiddenTimeSlots(String const& filename)
        -> Expected<ForbiddenTimeSlots>
    {
        // TODO
        return ForbiddenTimeSlots{};
    }

    void setForbiddenFields(Task& task, ForbiddenTimeSlots const& forbiddenTimeSlots)
    {
        // TODO
    }

    auto readInput(Config const& config)
        -> Expected<Task>
    {
        auto result { Task{} };
        
        // TODO: использовать функции, данные выше
        
        return result;
    }

}
