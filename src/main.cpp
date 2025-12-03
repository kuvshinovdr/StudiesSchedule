/// @file  main.cpp
#include "log.hpp"
#include "config.hpp"
#include <print>
#include <exception>
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

int main(int argc, char* argv[])
try
{
    auto config { parseCommandLineParameters(argc, argv) };
    
    if (config.version) {
        std::println("{}\n", Version);
        return 0;
    }

    if (config.help) {
        std::println("{}\n\n{}", Version, Help);
        return 0;
    }

    // TODO

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
