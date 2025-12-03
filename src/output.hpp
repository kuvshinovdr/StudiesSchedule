/// @file  output.hpp
/// @brief Формирование файлов результатов.
#ifndef STUDIES_SCHEDULE_OUTPUT_HPP
#define STUDIES_SCHEDULE_OUTPUT_HPP

#include "assignments.hpp"
#include "schedule.hpp"
#include "task.hpp"
#include "error_fwd.hpp"

namespace studies_schedule
{

    /// @brief            Сформировать строку CSV-файла, описывающую назначение в соответствии с данными задачи.
    /// @param assignment назначение
    /// @param task       исходная задача с названиями групп и т.п. данными
    /// @return           строка из значений, взятых в кавычки и разделённых запятыми: день недели, номер пары, аудитория, группа, преподаватель, предмет
    [[nodiscard]] auto toCsvRow(Assignment const& assignment, Task const& task)
        -> String;

    /// @brief             Сформировать и записать CSV-файл с назначениями.
    /// @param assignments назначения (только успешные)
    /// @param task        исходная задача с названиями групп и т.п. данными
    /// @param filename    путь к записываемому файлу
    /// @return            код ошибки
    auto writeAssignments(Assignments const& assignments, Task const& task, String const& filename)
        -> Expected<void>;



}

#endif//STUDIES_SCHEDULE_OUTPUT_HPP
