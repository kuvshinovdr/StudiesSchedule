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
        return readCsvData<Instructors>(filename, [](TableRow& row)
            {
                return !row.empty() ? Instructor { .id = std::move(row[0]), .name = std::move(row[1]) } : Instructor{};
            });
    }

    auto readGroups(String const& filename)
        -> Expected<Groups>
    {
 return readCsvData<Groups>(filename, [](TableRow& row)
            {
                return !row.empty() ? Group { .id = std::move(row[0]), .name = std::move(row[1]) } : Group{};
            });
    }

    auto readSubjects(String const& filename)
        -> Expected<Subjects>
    {
       return readCsvData<Subjects>(filename, [](TableRow& row)
            {
                return !row.empty() ? Subject { .id = std::move(row[0]), .name = std::move(row[1]) } : Subject{};
            });
    }

    auto readTimeSlots(String const& filename)
        -> Expected<TimeSlots>
    {
       return readCsvData<TimeSlots>(filename, [](TableRow& row)
            {
                return !row.empty() ? TimeSlot { .startTime = std::move(row[0]), .endTime = std::move(row[1]) } : TimeSlot{};
            });
    }

    auto readForbiddenTimeSlots(String const& filename)
        -> Expected<ForbiddenTimeSlots>
    {
        return readCsvData<ForbiddenTimeSlots>(filename, [](TableRow& row)
            {
                return !row.empty() ? ForbiddenTimeSlot { .startTime = std::move(row[0]), .endTime = std::move(row[1]) } : ForbiddenTimeSlot{};
            });
    }

    void setForbiddenFields(Task& task, ForbiddenTimeSlots const& forbiddenTimeSlots)
    {
            task.forbiddenTimeSlots = forbiddenTimeSlots;
    }

    auto readInput(Config const& config)
        -> Expected<Task>
    {
               auto result { Task{} };
        
        auto instructorsResult = readInstructors(config.input + "/instructors.csv");
        if (!instructorsResult) 
        {
            logError("Failed to read instructors: ", instructorsResult.error());
            return instructorsResult;
        }

        auto groupsResult = readGroups(config.input + "/groups.csv");
        if (!groupsResult) 
        {
            logError("Failed to read groups: ", groupsResult.error());
            return groupsResult;
        }

        auto subjectsResult = readSubjects(config.input + "/subjects.csv");
        if (!subjectsResult) 
        {
            logError("Failed to read subjects: ", subjectsResult.error());
            return subjectsResult;
        }

        auto timeSlotsResult = readTimeSlots(config.input + "/timeslots.csv");
        if (!timeSlotsResult) 
        {
            logError("Failed to read time slots: ", timeSlotsResult.error());
            return timeSlotsResult;
        }

        auto forbiddenSlotsResult = readForbiddenTimeSlots(config.input + "/forbidden.csv");
        if (!forbiddenSlotsResult) 
        {
            logError("Failed to read forbidden time slots: ", forbiddenSlotsResult.error());
            return forbiddenSlotsResult;
}
        result.instructors = std::move(instructorsResult.value());
        result.groups = std::move(groupsResult.value());
        result.subjects = std::move(subjectsResult.value());
        result.timeSlots = std::move(timeSlotsResult.value());
        setForbiddenFields(result, std::move(forbiddenSlotsResult.value()));
        return result;
    }

}
