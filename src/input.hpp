/// @file  input.hpp
/// @brief Чтение входных данных.
#ifndef STUDIES_SCHEDULE_INPUT_HPP
#define STUDIES_SCHEDULE_INPUT_HPP

#include "task.hpp"
#include "config.hpp"
#include "error_fwd.hpp"

namespace studies_schedule
{

    /// @brief          Прочитать входные данные.
    /// @param config   объект, содержащий пути к входным файлам
    /// @return         данные постановки задачи или ошибка
    [[nodiscard]] auto readInput(Config const& config)
        -> Expected<Task>;

}

#endif//STUDIES_SCHEDULE_INPUT_HPP
