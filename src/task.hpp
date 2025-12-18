/// @file  task.hpp
/// @brief Структуры данных, описывающие входные данные задачи составления расписания (т.е. постановку задачи).
#ifndef STUDIES_SCHEDULE_TASK_HPP
#define STUDIES_SCHEDULE_TASK_HPP

#include "time_slots.hpp"
#include "indexed_storage.hpp"

#include <unordered_map>

namespace studies_schedule
{

    using TaskIndex =
        TimeSlotIndex;

    struct Room
    {
        String          id          {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Room const&) const noexcept = default;
    };

    using Rooms =
        std::vector<Room>;

    struct Group
    {
        String          id          {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Group const&) const noexcept = default;
    };

    using Groups =
        std::vector<Group>;

    struct Instructor
    {
        String          name        {};
        TimeSlotIndices forbidden   {};

        [[nodiscard]] constexpr auto operator<=>(Instructor const&) const noexcept = default;
    };

    using Instructors =
        std::vector<Instructor>;

    struct Subject
    {
        String title            {};
        String groupId          {};
        String instructorName   {};

        [[nodiscard]] constexpr auto operator<=>(Subject const&) const noexcept = default;
    };

    using Subjects =
        std::vector<Subject>;


    [[nodiscard]] inline decltype(auto) id(TimeSlot const& timeSlot) noexcept
    {
        return timeSlot;
    }

    [[nodiscard]] inline auto id(Room const& room) noexcept
    {
        return StringView{room.id};
    }

    [[nodiscard]] inline auto id(Group const& group) noexcept
    {
        return StringView{group.id};
    }

    [[nodiscard]] inline auto id(Instructor const& instructor) noexcept
    {
        return StringView{instructor.name};
    }

    struct TimeSlotHash
    {
        [[nodiscard]] auto operator()(TimeSlot const& timeSlot) const noexcept
        {
            static auto const hasher { std::hash<String>{} };
            return hasher(timeSlot.dayOfWeek) ^ hasher(timeSlot.daySlot);
        }
    };

    struct StringHash
    {
        using is_transparent = void;

        template <typename StringLike>
        [[nodiscard]] constexpr auto operator()(StringLike&& str) const noexcept
        {
            return std::hash<StringView>{}(StringView{str});
        }
    };

    namespace impl
    {
        
        template <typename Item> struct TaskItemsByItem {}; // пусто: нет общего определения.
        // Конкретные версии:
        template <> struct TaskItemsByItem<TimeSlot>   { using type = TimeSlots;   };
        template <> struct TaskItemsByItem<Room>       { using type = Rooms;       };
        template <> struct TaskItemsByItem<Group>      { using type = Groups;      };
        template <> struct TaskItemsByItem<Instructor> { using type = Instructors; };
        template <> struct TaskItemsByItem<Subject>    { using type = Subjects;    };

        using TimeSlotToIndex =
            std::unordered_map<TimeSlot, TaskIndex, TimeSlotHash>;

        using StringToIndex =
            std::unordered_map<StringView, TaskIndex, StringHash, std::equal_to<>>;

        template <typename Items> struct TaskIndexFor { using type = StringToIndex;  }; // общее определение.
        // Специальные версии:
        template <> struct TaskIndexFor<TimeSlots> { using type = TimeSlotToIndex; };

        template <typename Items> 
        struct TaskBaseFor 
        {
            // Общее определение:
            using type = IndexedStorage<Items, typename TaskIndexFor<Items>::type>;
        };

        // На данный момент нет индексирования для предметов, но его можно будет добавить при необходимости.
        template <> struct TaskBaseFor<Subjects> { using type = BasicStorage<Subjects>; };

    }

    template <typename Items>
    using TaskBaseFor =
        typename impl::TaskBaseFor<Items>::type;

    template <typename Item>
    using TaskBaseByItem =
        TaskBaseFor<typename impl::TaskItemsByItem<Item>::type>;

    class Task
        : TaskBaseFor<TimeSlots>
        , TaskBaseFor<Rooms>
        , TaskBaseFor<Groups>
        , TaskBaseFor<Instructors>
        , TaskBaseFor<Subjects>
    {
    public:
        Task() noexcept = default;

        template <typename Items>
        [[nodiscard]] auto get() const noexcept
        {
            return TaskBaseFor<Items>::get();
        }

        template <typename Items>
        void set(Items&& items) noexcept
        {
            TaskBaseFor<Items>::set(std::move(items));
        }

        template <typename Item>
        [[nodiscard]] decltype(auto) get(TaskIndex index) const noexcept
        {
            return TaskBaseByItem<Item>::operator[](index);
        }

        template <typename Item, typename Key>
        [[nodiscard]] auto indexOf(Key const& key) const noexcept
        {
            return TaskBaseByItem<Item>::indexOf(key);
        }
    };

}

#endif//STUDIES_SCHEDULE_TASK_HPP
