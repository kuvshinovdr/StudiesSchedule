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

    // Шаблонная функция для записи расписания любого типа
    template<typename ScheduleType, typename GetNameFunc>
    auto writeScheduleTemplate(
        ScheduleType const& schedule,
        Task const& task,
        String const& filename,
        String const& scheduleTypeName,
        GetNameFunc getName
    ) -> Expected<void>
    {
        try {
            // Заголовок CSV
            String content = delimitedQuotedConcat(", ",
                "День недели",
                "Номер пары",
                scheduleTypeName,
                "Предмет",
                "Преподаватель",
                "Группа",
                "Аудитория"
            ) + "\n";

            // Проходим по всем временным слотам
            for (size_t timeSlot = 0; timeSlot < schedule.size(); ++timeSlot) {
                auto const& assignmentPtr = schedule[timeSlot];

                if (assignmentPtr) {
                    // Получаем назначение
                    auto const& assignment = *assignmentPtr;

                    // Получаем имя в зависимости от типа расписания
                    String name = getName(assignment, task);

                    // Преобразуем временной слот в день и номер пары
                    // Предполагаем, что в день 6 пар (0-5)
                    size_t day = timeSlot / 6; // 0-4 (пн-пт)
                    size_t lesson = timeSlot % 6 + 1; // 1-6

                    // Получаем остальные данные из задачи
                    String subject = task.getSubjectName(assignment.subjectId).value_or("Неизвестно");
                    String instructor = task.getInstructorName(assignment.instructorId).value_or("Неизвестно");
                    String group = task.getGroupName(assignment.groupId).value_or("Неизвестно");
                    String room = task.getRoomName(assignment.roomId).value_or("Неизвестно");

                    // Формируем строку
                    content += delimitedQuotedConcat(", ",
                        std::to_string(day),
                        std::to_string(lesson),
                        name,
                        subject,
                        instructor,
                        group,
                        room
                    ) + "\n";
                }
            }

            // Записываем в файл
            return stringToFile(filename, content);
        }
        catch (std::exception const& e) {
            logError("Ошибка при формировании расписания: " + String(e.what()));
            return make_unexpected(Error::OutputError);
        }
        catch (...) {
            logError("Неизвестная ошибка при формировании расписания");
            return make_unexpected(Error::OutputError);
        }
    }

    auto writeGroupSchedule(GroupSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // Лямбда для получения названия группы
        auto getGroupName = [&task](Assignment const& assignment, Task const&) {
            return task.getGroupName(assignment.groupId).value_or("Неизвестная группа");
            };

        return writeScheduleTemplate(schedule, task, filename, "Группа", getGroupName);
    }

    auto writeRoomSchedule(RoomSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // Лямбда для получения названия аудитории
        auto getRoomName = [&task](Assignment const& assignment, Task const&) {
            return task.getRoomName(assignment.roomId).value_or("Неизвестная аудитория");
            };

        return writeScheduleTemplate(schedule, task, filename, "Аудитория", getRoomName);
    }

    auto writeInstructorSchedule(InstructorSchedule const& schedule, Task const& task, String const& filename)
        -> Expected<void>
    {
        // Лямбда для получения имени преподавателя
        auto getInstructorName = [&task](Assignment const& assignment, Task const&) {
            return task.getInstructorName(assignment.instructorId).value_or("Неизвестный преподаватель");
            };

        return writeScheduleTemplate(schedule, task, filename, "Преподаватель", getInstructorName);
    }

}