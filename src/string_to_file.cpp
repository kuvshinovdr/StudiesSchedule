/// @file  string_to_file.cpp
#include "string_to_file.hpp"
#include <fstream>
#include <utility>

namespace studies_schedule
{

    [[nodiscard]] static auto toIosMode(FileUpdateMode mode) noexcept
        -> std::ios_base::openmode
    {
        switch (mode) {
        case FileUpdateMode::OnlyNew:
            // TODO: report logical error
        case FileUpdateMode::Rewrite:
            return std::ios::out | std::ios::binary;
        case FileUpdateMode::Append:
            return std::ios::out | std::ios::binary | std::ios::app;
        }

        std::unreachable();
    }

    [[nodiscard]] static bool fileAvailableForWrite(FilePath const& filename, FileUpdateMode mode) noexcept
    {
        if (mode == FileUpdateMode::OnlyNew) {
            [[maybe_unused]] auto ec { std::error_code{} };
            return std::filesystem::exists(filename, ec);
        }

        return true;
    }

    // TODO: может быть сделать свой класс категории ошибок
    auto stringToFile(
        FilePath const& filename, 
        StringView      data, 
        FileUpdateMode  mode
        ) noexcept 
        -> StringToFileResult
    {
        if (!fileAvailableForWrite(filename, mode)) {
            return std::unexpected(std::make_error_code(std::errc::file_exists));
        }

        auto file { std::ofstream(filename, toIosMode(mode)) };

        if (!file.is_open()) {
            return std::unexpected(std::make_error_code(std::errc::read_only_file_system));
        }

        if (std::cmp_greater(data.size(), std::numeric_limits<std::streamsize>::max())) {
            return std::unexpected(std::make_error_code(std::errc::value_too_large));
            // Эту ситуацию можно решить без ошибки, но её возникновение в реальности невероятно.
        }

        file.write(data.data(), static_cast<std::streamsize>(data.size()));

        if (file.bad()) {
            return std::unexpected(std::make_error_code(std::errc::interrupted));
        }

        return {};
    }

}
