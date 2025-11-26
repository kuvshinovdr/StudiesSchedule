/// @file  file_to_string.hpp
/// @brief Функция чтения файла в строку.
#ifndef STUDIES_SCHEDULE_FILE_TO_STRING_HPP
#define STUDIES_SCHEDULE_FILE_TO_STRING_HPP

#include "error_fwd.hpp"
#include "file_operations_fwd.hpp"
#include "string_operations_fwd.hpp"

namespace studies_schedule
{

    using FileToStringResult = Expected<String>;

    /// @brief Прочитать заданный файл в память целиком как двоичные данные и вернуть как объект String. 
    [[nodiscard]] auto fileToString(FilePath const& filename) noexcept
        -> FileToStringResult;

}

#endif//STUDIES_SCHEDULE_FILE_TO_STRING_HPP
