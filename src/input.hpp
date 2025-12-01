/// @file  input.hpp
/// @brief Чтение входных данных.
#ifndef STUDIES_SCHEDULE_INPUT_HPP
#define STUDIES_SCHEDULE_INPUT_HPP

#include "input_data_model.hpp"
#include "config.hpp"

namespace studies_schedule
{

    /// @brief          Прочитать входные данные.
    /// @param config   объект, содержащий пути к входным файлам
    /// @return         данные постановки задачи
    [[nodiscard]] auto readInput(Config const& config)
        -> Task;

}

#endif//STUDIES_SCHEDULE_INPUT_HPP
