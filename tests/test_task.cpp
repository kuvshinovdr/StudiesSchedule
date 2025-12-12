/// @file  test_task.cpp
#include <task.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("task")
{

    TEST_CASE("BasicStorage")
    {
        class SubjectStorage
            : public BasicStorage<Subjects>
        {
        public:
            constexpr SubjectStorage() noexcept = default;
            using BasicStorage<Subjects>::set;
        };
        
        auto calculus
        {
            Subject
            { 
                .title = "Calculus", 
                .groupId = "Math-1", 
                .instructorName = "prof. Andersen"
            }
        };

        auto algebra
        {
            Subject 
            { 
                .title = "Algebra",  
                .groupId = "CSci-1", 
                .instructorName = "prof. Seeman"
            }
        };

        auto subjects { SubjectStorage{} };

        subjects.set(Subjects{ calculus, algebra });

        CHECK(subjects.get().size() == 2);
        CHECK(subjects[0] == calculus);
        CHECK(subjects[1] == algebra);
    }

    TEST_CASE("IndexedStorage")
    {
        class IndexedRooms
            : public IndexedStorage<Rooms, std::unordered_map<StringView, std::int32_t, StringHash>>
        {
        public:
            constexpr IndexedRooms() noexcept = default;
        };

        auto rooms { IndexedRooms{} };

        rooms.set(Rooms
            {
                Room { .id = "532" },
                Room { .id = "514" },
                Room { .id = "150" },
                Room { .id = "611" },
            });

        CHECK(rooms[0].id == "532");
        CHECK(rooms[1].id == "514");
        CHECK(rooms[2].id == "150");
        CHECK(rooms[3].id == "611");

        CHECK(*rooms.indexOf("611"sv) == 3);
        CHECK(*rooms.indexOf("514"sv) == 1);
        CHECK(*rooms.indexOf("150"sv) == 2);
        CHECK(*rooms.indexOf("532"sv) == 0);

        CHECK(!rooms.indexOf("610"sv));
        CHECK(!rooms.indexOf("444"sv));
    }

    TEST_CASE("Task")
    {
        auto task { Task{} };

        task.set<Rooms>(
            Rooms
            { 
                Room{.id = "101"}, 
                Room{.id = "202"}, 
            });

        task.set<Groups>(
            Groups
            { 
                Group{.id = "A-1"}, 
                Group{.id = "B-2"},
            });

        task.set<Instructors>(
            Instructors
            { 
                Instructor{.name = "Alice"}, 
                Instructor{.name = "Bob"},
            });

        task.set<TimeSlots>(
            TimeSlots
            {
                TimeSlot{.dayOfWeek = "Mon", .daySlot = "1"}, 
                TimeSlot{.dayOfWeek = "Tue", .daySlot = "2"},
                TimeSlot{.dayOfWeek = "Tue", .daySlot = "3"},
            });

        task.set<Subjects>(
            Subjects
            {
                Subject{.title = "Math", .groupId = "A-1", .instructorName = "Alice"},
                Subject{.title = "Prog", .groupId = "A-1", .instructorName = "Bob"},
                Subject{.title = "Physics", .groupId = "B-2", .instructorName = "Alice"},
                Subject{.title = "Numeric", .groupId = "B-2", .instructorName = "Bob"},
            });

        CHECK(task.get<Rooms>().size() == 2);
        CHECK(*task.indexOf<Room>("101") == 0);
        CHECK(*task.indexOf<Room>("202") == 1);
        CHECK(!task.indexOf<Room>("999"));

        CHECK(task.get<Groups>().size() == 2);
        CHECK(*task.indexOf<Group>("B-2") == 1);
        CHECK(!task.indexOf<Group>("B-3"));
        CHECK(task.get<Group>(0).id == "A-1"sv);

        CHECK(task.get<Instructors>().size() == 2);
        CHECK(*task.indexOf<Instructor>("Alice"sv) == 0);
        CHECK(!task.indexOf<Instructor>(""));

        CHECK(task.get<TimeSlots>().size() == 3);
        CHECK(*task.indexOf<TimeSlot>(TimeSlot{.dayOfWeek = "Mon", .daySlot = "1"}) == 0);
        CHECK(!task.indexOf<TimeSlot>(TimeSlot{}));
        CHECK(task.get<TimeSlot>(2).dayOfWeek == "Tue");

        CHECK(task.get<Subjects>().size() == 4);
        CHECK(task.get<Subject>(3).title == "Numeric"sv);
    }

}
