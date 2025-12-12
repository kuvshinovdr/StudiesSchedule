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

}
