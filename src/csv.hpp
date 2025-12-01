/// @file  csv.hpp
/// @brief Реализация чтения CSV.
#ifndef STUDIES_SCHEDULE_CSV_HPP
#define STUDIES_SCHEDULE_CSV_HPP

#include "error_fwd.hpp"
#include "string_operations_fwd.hpp"
#include <vector>

namespace studies_schedule
{

    using TableRow =
        std::vector<String>;

    using Table =
        std::vector<TableRow>;

    [[nodiscard]] auto parseCsv(StringView input)
        -> Expected<Table>;

}

#endif//STUDIES_SCHEDULE_CSV_HPP
