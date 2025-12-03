/// @file  string_operations.hpp
/// @brief Дополнительные функции для работы со строками.
#ifndef STUDIES_SCHEDULE_STRING_OPERATIONS_HPP
#define STUDIES_SCHEDULE_STRING_OPERATIONS_HPP

#include "string_operations_fwd.hpp"
#include <format>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <type_traits>

namespace studies_schedule
{

    constexpr auto Quote        { '"' };
    constexpr auto QuoteQuote   { "\"\""sv };

    template <typename T>
    concept StringLike =
        std::same_as<std::remove_const_t<std::remove_reference_t<T>>, String::value_type> ||
        std::convertible_to<T, StringView>;

    static_assert(StringLike<String>);
    static_assert(StringLike<StringView>);
    static_assert(StringLike<String::value_type>);
    static_assert(StringLike<String::value_type const*>);

    namespace impl
    {

        [[nodiscard]] constexpr auto size(String::value_type) noexcept
        {
            return 1;
        }

        [[nodiscard]] constexpr auto size(String::value_type const* cstring) noexcept
        {
            return StringView(cstring).size();
        }

        template <std::ranges::sized_range Range>
        [[nodiscard]] constexpr auto size(Range const& range) noexcept
        {
            using std::ranges::size;
            return size(range);
        }

    }

    template <typename... Ranges>
    [[nodiscard]] constexpr auto concatLength(Ranges&&... ranges) noexcept
    {
        using impl::size;
        return (size(ranges) + ...);
    }

    template <StringLike... Parts>
    [[nodiscard]] constexpr auto concat(Parts&&... parts)
        -> String
    {
        auto result { String {} };
        result.reserve(concatLength(parts...));
        (result += ... += parts);
        return result;
    }

    [[nodiscard]] constexpr auto quoted(String::value_type field)
        -> String
    {
        return field == Quote? "\"\"\"\""s: std::format("\"{}\"", field);
    }

    [[nodiscard]] constexpr auto quoted(StringView field)
        -> String
    {
        auto result { String{} };

        using impl::size;
        result.resize(2 + size(field) + std::ranges::count(field, Quote));

        auto writePos { result.data() };
        *writePos++ = Quote;

        for (auto ch : field) {
            *writePos++ = ch;
            if (ch == Quote) {
                *writePos++ = Quote;
            }
        }

        *writePos++ = Quote;
        return result;
    }

    template <StringLike Delim, StringLike First, StringLike... Parts>
    [[nodiscard]] constexpr auto delimitedConcat(Delim&& delim, First&& first, Parts&&... parts)
    {
        return concat(std::forward<First>(first), concat(delim, std::forward<Parts>(parts))...);
    }

    template <StringLike Delim, StringLike... Parts>
    [[nodiscard]] constexpr auto delimitedQuotedConcat(Delim&& delim, Parts&&... parts)
    {
        return delimitedConcat(std::forward<Delim>(delim), quoted(std::forward<Parts>(parts))...);
    }

}

#endif//STUDIES_SCHEDULE_STRING_OPERATIONS_HPP
