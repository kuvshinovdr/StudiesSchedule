/// @file  input.hpp
/// @brief Чтение входных данных.
#ifndef STUDIES_SCHEDULE_INPUT_HPP
#define STUDIES_SCHEDULE_INPUT_HPP

#include "time_slots.hpp"
#include "task.hpp"
#include "config.hpp"
#include "error_fwd.hpp"

namespace studies_schedule
{

    /// @brief          Прочитать из CSV-файла информацию об аудиториях (на данный момент только идентификаторы).
    /// @param filename имя файла
    /// @return         массив описаний аудиторий (пустые forbidden).
    [[nodiscard]] auto readRooms(String const& filename)
        -> Expected<Rooms>;

    /// @brief          Прочитать из CSV-файла информацию о преподавателях (на данный момент только имена).
    /// @param filename имя файла
    /// @return         массив описаний преподавателей (пустые forbidden).
    [[nodiscard]] auto readInstructors(String const& filename)
        -> Expected<Instructors>;

    /// @brief          Прочитать из CSV-файла информацию о группах (на данный момент только идентификаторы).
    /// @param filename имя файла
    /// @return         массив описаний групп (пустые forbidden).
    [[nodiscard]] auto readGroups(String const& filename)
        -> Expected<Groups>;

    /// @brief          Прочитать из CSV-файла информацию о предметах (название, группа, преподаватель).
    /// @param filename имя файла
    /// @return         массив описаний предметов.
    [[nodiscard]] auto readSubjects(String const& filename)
       -> Expected<Subjects>;

    /// @brief          Прочитать из CSV-файла информацию о временных слотах (день недели, номер в течении дня).
    /// @param filename имя файла
    /// @return         массив описаний временных слотов.
    [[nodiscard]] auto readTimeSlots(String const& filename)
        -> Expected<TimeSlots>;

    struct ForbiddenTimeSlot
    {
        enum class IdOwner
        {
            Room,
            Group,
            Instructor,
        };

        String  dayOfWeek;
        String  daySlot;
        IdOwner idOwner { IdOwner::Room };
        String  id;
    };

    using ForbiddenTimeSlots =
        std::vector<ForbiddenTimeSlot>;

    /// @brief          Прочитать из файла запрещённые слоты.
    /// @param filename имя файла
    /// @return         набор запрещённых слотов
    /// 
    /// Поле idOwner -- предпоследнее, может иметь значения "room", "stuff" или "group"
    /// (допустимо сокращение до первой буквы: "r", "s" или "g").
    [[nodiscard]] auto readForbiddenTimeSlots(String const& filename)
        -> Expected<ForbiddenTimeSlots>;

    /// @brief                    Записать поля forbidden во всех элементах Task.
    /// @param task               устанавливаемая задача
    /// @param forbiddenTimeSlots список запрещённых временных слотов
    void setForbiddenFields(Task& task, ForbiddenTimeSlots const& forbiddenTimeSlots);

    /// @brief        Прочитать входные данные.
    /// @param config объект, содержащий пути к входным файлам
    /// @return       данные постановки задачи или ошибка
    [[nodiscard]] auto readInput(Config const& config)
        -> Expected<Task>;

}

#endif//STUDIES_SCHEDULE_INPUT_HPP
