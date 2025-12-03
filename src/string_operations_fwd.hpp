/// @file  string_operations_fwd.hpp
/// @brief Общие объявления для операций со строками.
#ifndef STUDIES_SCHEDULE_STRING_OPERATIONS_FWD_HPP
#define STUDIES_SCHEDULE_STRING_OPERATIONS_FWD_HPP

#ifdef _MSC_VER
#include <ostream>
#endif
#include <string>
#include <string_view>

namespace studies_schedule
{

    using String =
        std::string;

    using StringView = 
        std::string_view;

    using namespace std::string_literals;
    using namespace std::string_view_literals;

}

#endif//STUDIES_SCHEDULE_STRING_OPERATIONS_FWD_HPP
