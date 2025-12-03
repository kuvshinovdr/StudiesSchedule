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
        // TODO
        return {};
    }

    auto writeAssignments(Assignments const& assignments, Task const& task, String const& filename)
        -> Expected<void>
    {
        // TODO
        return {};
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
