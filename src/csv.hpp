/// @file  csv.hpp
/// @brief Реализация чтения CSV.
#ifndef STUDIES_SCHEDULE_CSV_HPP
#define STUDIES_SCHEDULE_CSV_HPP

#include "error_fwd.hpp"
#include "string_operations_fwd.hpp"
#include <vector>

namespace studies_schedule
{

    /// @brief Строка таблицы -- результата чтения CSV.
    using TableRow =
        std::vector<String>;

    /// @brief Таблица -- результат чтения CSV.
    using Table =
        std::vector<TableRow>;

    /// @brief       Выполнить разбор CSV-файла.
    /// @param input содержимое CSV-файла
    /// @return      таблица или ошибка
    /// 
    /// Дополнительная информация об ошибках записывается в лог, используя функции из log.hpp.
    [[nodiscard]] auto parseCsv(StringView input)
        -> Expected<Table>;

}

#endif//STUDIES_SCHEDULE_CSV_HPP
