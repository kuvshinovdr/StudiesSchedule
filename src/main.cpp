/// @file  main.cpp
#include "log.hpp"
#include "config.hpp"
#include "input.hpp"
#include "solve.hpp"
#include "separate_assignments.hpp"
#include "prepare_schedule.hpp"
#include "output.hpp"
#include "string_operations.hpp"

#include <format>
#include <print>
#include <stdexcept>
#include <typeinfo>

using namespace studies_schedule;

constexpr auto Version
{
    "StudiesSchedule v.1.0"sv
};

constexpr auto Help
{
    "The program tries to make a schedule for organizing educational process.\n"
    "Input and output files use CSV format.\n\n"
    "The following command line parameters are expected:\n\n"
    "--help    : show this help and exit;\n"
    "--version : show only version information and exit;\n"
    "--attempts: how many attempts to try in order to get a better result;\n"
    "--input   : set the shared path to input files;\n"
    "--output  : set the path to output files;\n"
    "--rooms   : set the name of the rooms data file, rooms.csv by default;\n"
    "--stuff   : set the name of the stuff data file, stuff.csv by default;\n"
    "--groups  : set the name of the groups data file, groups.csv by default;\n"
    "--subjects: set the name of the subjects data file, subjects.csv by default;\n"
    "--timeslots: time slot listing in choice desirability order;\n"
    "--forbidden: forbidden time slots for rooms, groups and stuff members.\n\n"
    "Input format:\n\n"
    "- rooms: a listing of unique room identifiers;\n"
    "- stuff: a listing of unique names of stuff members;\n"
    "- groups: a listing of unique group identifiers;\n"
    "- subjects: a table of subject appointments: subject title, group, instructor;\n"
    "- timeslots: a table of time slots: day of week, index within the day;\n"
    "- forbidden: day of week, index within the day, room|group|stuff, id or name.\n\n"
    "Output format:\n\n"
    "- group_id.csv (for each group): day, index, room, subject, instructor;\n"
    "- room_id.csv (for each room): day, index, subject, group, instructor;\n"
    "- stuff_name.csv (for each stuff member): day, index, room, subject, group;\n"
    "- assigned.csv: time slot index, room, group, instructor, subject;\n"
    "- unassigned.csv: time slot index, room, group, instructor, subject.\n"
    "If the task succeeded, the unassigned table will be empty.\n"
    ""sv
};

constexpr auto FileExtension        { ".csv"       };
constexpr auto AssignedFilename     { "assigned"   };
constexpr auto UnassignedFilename   { "unassigned" };
constexpr auto GroupFilename        { "group_"     };
constexpr auto RoomFilename         { "room_"      };
constexpr auto StuffFilename        { "stuff_"     };

constexpr auto ErrorOnAssigned       { "on writing assigned assignments"sv   };
constexpr auto ErrorOnUnassigned     { "on writing unassigned assignments"sv };
constexpr auto ErrorOnWritingGroups  { "on writing group schedule"sv         };
constexpr auto ErrorOnWritingRooms   { "on writing room schedule"sv          };
constexpr auto ErrorOnWritingStuff   { "on writing stuff schedule"sv         };

int main(int argc, char* argv[])
try
{
    log::debug("parsing command line parameters");

    auto config { parseCommandLineParameters(argc, argv) };
    
    if (config.version) {
        std::println("{}\n", Version);
        return 0;
    }

    if (config.help) {
        std::println("{}\n\n{}", Version, Help);
        return 0;
    }

    log::debug("reading input files");

    auto input  { readInput(config) };
    
    if (!input) {
        throw std::runtime_error("Failed to parse input files. Exiting.");
    }

    log::debug("solving the task");

    auto task   { std::move(input.value()) };

    auto assigned   { Assignments{} };
    auto unassigned { Assignments{} };

    for (int attempt = 0; attempt < config.attempts; ++attempt) {
        log::debug("attempt {}", attempt);

        auto assignments { solve(task) };
        
        if (!simpleSanityCheck(task, assignments)) {
            log::error("attempt {} assignments sanity check failed (internal error)", attempt);
            continue;
        }

        if (auto unassignedSubjects = findUnassignedSubjects(task, assignments); !unassignedSubjects.empty()) {
            log::error("attempt {}: {} subjects have found their place in our schedule", attempt, unassignedSubjects.size());
            
            for (auto& subject : unassignedSubjects) {
                log::info(" -- {} {} {}", subject.title, subject.groupId, subject.instructorName);
            }

            continue;
        }

        // TODO: оценка качества
        auto separate { separateAssignments(assignments, static_cast<TimeSlotIndex>(task.timeSlots.size())) };
        
        if (separate.unassigned.size() < unassigned.size()) {
            assigned    = std::move(separate.assigned);
            unassigned  = std::move(separate.unassigned);
        }
    }

    log::debug("writing assignments");

    if (auto expected = writeAssignments(assigned, task, concat(config.output, AssignedFilename, FileExtension));
        !expected)
    {
        log::error(expected.error(), ErrorOnAssigned);
    }

    if (auto expected = writeAssignments(unassigned, task, concat(config.output, UnassignedFilename, FileExtension));
        !expected)
    {
        log::error(expected.error(), ErrorOnUnassigned);
    }

    log::debug("writing group schedules");

    for (GroupIndex group = 0; group < static_cast<GroupIndex>(task.groups.size()); ++group) {
        auto groupSchedule { makeGroupSchedule(group, assigned, task) };
        
        auto expected 
        {
            writeGroupSchedule(groupSchedule, task, 
                concat(config.output, GroupFilename, task.groups[group].id, FileExtension))
        };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingGroups);
        }
    }

    log::debug("writing instructor schedules");

    for (InstructorIndex instructor = 0; instructor < static_cast<InstructorIndex>(task.instructors.size()); ++instructor) {
        auto instructorSchedule { makeInstructorSchedule(instructor, assigned, task) };
        
        auto expected
        {
            writeInstructorSchedule(instructorSchedule, task,
                concat(config.output, StuffFilename, task.instructors[instructor].name, FileExtension))
        };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingStuff);
        }
    }
    
    log::debug("writing room schedules");
    
    for (RoomIndex room = 0; room < static_cast<RoomIndex>(task.rooms.size()); ++room) {
        auto roomSchedule { makeRoomSchedule(room, assigned, task) };
        
        auto expected
        {
            writeRoomSchedule(roomSchedule, task,
                concat(config.output, RoomFilename, task.rooms[room].id, FileExtension))
        };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingRooms);
        }
    }   
    
    log::debug("done");
    
    return 0;
}
catch (std::exception const& e)
{
    std::println("Failed due to exception ({}): {}\n", typeid(e).name(), e.what());
    return -1;
}
catch (...)
{
    std::println("Failed due to unknown exception\n");
    return -1;
}
