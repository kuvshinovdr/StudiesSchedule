/// @file  file_to_string.cpp
#include "file_to_string.hpp"
#include <fstream>
#include <utility>

namespace studies_schedule
{

    auto fileToString(FilePath const& filename) noexcept
        -> FileToStringResult
    {
        // TODO: свой класс категории ошибок
        auto        ec       { std::error_code{} };
        auto const  fileSize { std::filesystem::file_size(filename, ec) };

        if (ec) {
            return std::unexpected(ec);
        }

        if (std::cmp_greater(fileSize, std::numeric_limits<std::size_t>::max())
         || std::cmp_greater(fileSize, std::numeric_limits<std::streamsize>::max())) 
        {
            return std::unexpected(std::make_error_code(std::errc::file_too_large));
        }

        auto const  dataSize { static_cast<std::size_t>(fileSize) };
        auto        result   { String{} };
        try {
            result.resize(dataSize);
        } catch (...) {
            return std::unexpected(std::make_error_code(std::errc::not_enough_memory));
        }

        auto file { std::ifstream(filename, std::ios::binary) };
        
        if (!file.is_open()) {
            return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
        }

        file.read(result.data(), static_cast<std::streamsize>(dataSize));
        
        if (std::cmp_not_equal(file.gcount(), dataSize)) {
            return std::unexpected(std::make_error_code(std::errc::interrupted));
        }

        return result;
    }

}
