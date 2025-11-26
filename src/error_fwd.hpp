/// @file  error_fwd.hpp
/// @brief Объявление ErrorCode.
#ifndef STUDIES_SCHEDULE_ERROR_FWD_HPP
#define STUDIES_SCHEDULE_ERROR_FWD_HPP

#include <expected>
#include <system_error>

namespace studies_schedule
{

    using ErrorCode =
        std::error_code;

    template <typename T>
    using Expected =
        std::expected<T, ErrorCode>;

}

#endif//STUDIES_SCHEDULE_ERROR_FWD_HPP
