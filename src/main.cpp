/// @file  main.cpp
#include "log.hpp"
#include "config.hpp"
#include "input.hpp"
#include "solve.hpp"
#include "separate_assignments.hpp"
#include "prepare_schedule.hpp"
#include "output.hpp"
#include "string_operations.hpp"

#include <cstdlib>
#include <stdexcept>
#include <typeinfo>
#include <format>
#include <print>
#include <ranges>

using namespace studies_schedule;

constexpr auto Version
{
    "StudiesSchedule v.1.0 built on " __DATE__ " " __TIME__ ""sv
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

constexpr auto AssignedFnFmt    { "{}assigned.csv"sv    };
constexpr auto UnassignedFnFmt  { "{}unassigned.csv"sv  };
constexpr auto GroupFnFmt       { "{}group_{}.csv"sv    };
constexpr auto RoomFnFmt        { "{}room_{}.csv"sv     };
constexpr auto StuffFnFmt       { "{}stuff_{}.csv"sv    };

constexpr auto ErrorOnInput          { "on parsing input files"sv };
constexpr auto ErrorOnAssigned       { "on writing assigned assignments"sv   };
constexpr auto ErrorOnUnassigned     { "on writing unassigned assignments"sv };
constexpr auto ErrorOnWritingGroups  { "on writing group schedule"sv         };
constexpr auto ErrorOnWritingRooms   { "on writing room schedule"sv          };
constexpr auto ErrorOnWritingStuff   { "on writing stuff schedule"sv         };

constexpr auto DebugParsingCli         { "parsing command line parameters"sv };
constexpr auto DebugReadingInput       { "reading input files"sv             };
constexpr auto DebugSolvingTask        { "solving the task"sv                };
constexpr auto DebugWritingAssignments { "writing assignments"sv             };
constexpr auto DebugWritingGroups      { "writing group schedules"sv         };
constexpr auto DebugWritingRooms       { "writing room schedules"sv          };
constexpr auto DebugWritingStuff       { "writing stuff schedules"sv         };
constexpr auto DebugDone               { "done"sv                            };

int main(int argc, char* argv[])
try
{
    //===================================================================================
    log::debug(DebugParsingCli);

    auto config { parseCommandLineParameters(argc, argv) };
    
    if (config.version) {
        std::println("{}\n", Version);
        return 0;
    }

    if (config.help) {
        std::println("{}\n\n{}", Version, Help);
        return 0;
    }

    //===================================================================================
    log::debug(DebugReadingInput);

    auto input  { readInput(config) };
    
    if (!input) {
        log::fatal(input.error(), ErrorOnInput);
    }

    //===================================================================================
    log::debug(DebugSolvingTask);

    auto task   { std::move(input.value()) };

    auto assigned   { Assignments{} };
    auto unassigned { Assignments{} };

    for (auto attempt = int(0); attempt < config.attempts; ++attempt) {
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

        auto separate { separateAssignments(assignments, static_cast<TimeSlotIndex>(task.timeSlots.size())) };
        
        auto const newIsBetter
        {
            separate.unassigned.size() < unassigned.size() ||
            (separate.unassigned.size() == unassigned.size() &&
                isBetter(separate.assigned, assigned, task))
        };

        if (newIsBetter) {
            assigned    = std::move(separate.assigned);
            unassigned  = std::move(separate.unassigned);
        }
    }

    //===================================================================================
    log::debug(DebugWritingAssignments);

    auto const assignedFn   { std::format(AssignedFnFmt,   StringView{config.output}) };
    auto const unassignedFn { std::format(UnassignedFnFmt, StringView{config.output}) };

    if (auto expected = writeAssignments(assigned, task, assignedFn); !expected) {
        log::error(expected.error(), ErrorOnAssigned);
    }

    if (auto expected = writeAssignments(unassigned, task, unassignedFn); !expected) {
        log::error(expected.error(), ErrorOnUnassigned);
    }

    //===================================================================================
    log::debug(DebugWritingGroups);

    for (auto&& [i, group]: std::views::enumerate(task.groups)) {
        auto const schedule { makeGroupSchedule(i, assigned, task)             };
        auto const filename { std::format(GroupFnFmt, config.output, group.id) };
        auto const expected { writeGroupSchedule(schedule, task, filename)     };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingGroups);
        }
    }
    
    //===================================================================================
    log::debug(DebugWritingRooms);
    
    for (auto&& [i, room]: std::views::enumerate(task.rooms)) {
        auto const schedule { makeRoomSchedule(i, assigned, task)            };
        auto const filename { std::format(RoomFnFmt, config.output, room.id) };        
        auto const expected { writeRoomSchedule(schedule, task, filename)    };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingRooms);
        }
    }

    //===================================================================================
    log::debug(DebugWritingStuff);

    for (auto&& [i, stuff]: std::views::enumerate(task.instructors)) {
        auto const schedule { makeInstructorSchedule(i, assigned, task)          };
        auto const filename { std::format(StuffFnFmt, config.output, stuff.name) };
        auto const expected { writeInstructorSchedule(schedule, task, filename)  };

        if (!expected) {
            log::error(expected.error(), ErrorOnWritingStuff);
        }
    }
    
    //===================================================================================
    log::debug(DebugDone);
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
