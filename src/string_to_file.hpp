/// @file  string_to_file.hpp
/// @brief Функция записи строки в файл.
#ifndef STUDIES_SCHEDULE_STRING_TO_FILE_HPP
#define STUDIES_SCHEDULE_STRING_TO_FILE_HPP

#include "error_fwd.hpp"
#include "file_operations_fwd.hpp"
#include "string_operations_fwd.hpp"

namespace studies_schedule
{

    using StringToFileResult = Expected<void>;

    /// @brief Что делать, если файл, который мы хотим записать, уже существует.
    enum class FileUpdateMode
    {
        OnlyNew, ///< ошибка, если файл уже есть
        Rewrite, ///< перезаписать, если файл уже есть
        Append,  ///< дописать данные в конец файла, если он уже есть
    };

    /// @brief Записать данные StringView в заданный файл как двоичные данные.
    auto stringToFile(
        FilePath const& filename, 
        StringView      data, 
        FileUpdateMode  mode = FileUpdateMode::Rewrite
        ) noexcept 
        -> StringToFileResult;

}

#endif//STUDIES_SCHEDULE_STRING_TO_FILE_HPP
