/// @file  output.cpp
#include "output.hpp"
#include "string_to_file.hpp"
#include "string_operations.hpp"
#include "log.hpp"

namespace studies_schedule
{

    auto toCsvRow(Assignment const& assignment, Task const& task)
        -> String
    {

        auto const& timeSlot = task.get<TimeSlots>()[assignment.timeSlot];
        auto const& room = task.get<Rooms>()[assignment.room];
        auto const& group = task.get<Groups>()[assignment.group];
        auto const& instructor = task.get<Instructors>()[assignment.instructor];
        auto const& subject = task.get<Subjects>()[assignment.subject];
        return delimitedQuotedConcat(", ", timeSlot, room, group, instructor, subject);
    };
    }

    auto writeAssignments(Assignments const& assignments, Task const& task, String const& filename)
        -> Expected<void>
    {
        Vector<String> lines;
        lines.reserve(assignments.size());

        for (auto const& assignment : assignments) {
            Line.push_back(toCsvRow(assignment, task));
        }
        
        String text;

        for (size_t i = 0; i < line.size(); ++i) {
            text += lines[i];
            if (i != lines.size() - 1) {
                text += "\n";
            }
        }

        return stringToFile(text, filename);
    }

    auto writeGroupSchedule(GroupSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // TODO
        return {};
    }

    auto writeRoomSchedule(RoomSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // TODO
        return {};
    }

    auto writeInstructorSchedule(InstructorSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // TODO
        return {};
    }

}
