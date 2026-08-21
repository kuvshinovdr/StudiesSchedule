/// @file  test_output.cpp
#include <iostream>
#include <output.hpp>
#include <doctest.h>

using namespace studies_schedule;
using namespace std;

TEST_SUITE("output")
{

    TEST_CASE("toCsvRow")
    {
        Task task;

        TimeSlots timeSlots = { {"Понедельник", "1"}, {"Вторник", "5"} };
        task.set<TimeSlots>(timeSlots);

        Rooms rooms = { "514", "513" };
        task.set<Rooms>(rooms);

        Groups groups = { "Группа 202", "Группа 201", };
        task.set<Groups>(groups);

        Instructors instructors = { "Рекант М.А.", "Кувшинов Д.Р." };
        task.set<Instructors>(instructors);

        Subjects subjects = { "Матанализ", "Алгоритмический анализ" };
        task.set<Subjects>(subjects);

        Assignment assignment{ 0, 1, 1, 0, 0 };

        String actual = toCsvRow(assignment, task);
        String expected = "\"Понедельник 1\", \"513\", \"Группа 201\", \"Рекант М.А.\", \"Матанализ\""

        if (actual != expected) {
            cerr << "FAIL: actual != expected";
            cerr << "  Expected: " << expected << "\n";
            cerr << "  Actual:   " << actual << "\n";
        }
        else 
            cout << "No fail were found :)"
    }

}