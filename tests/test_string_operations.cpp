/// @file  test_string_operations.cpp
#include <string_operations.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("string operations")
{

    TEST_CASE("concatLength")
    {
        CHECK(concatLength('a') == 1);
        CHECK(concatLength("aa") == 2);
        CHECK(concatLength('a', "bbb", "", "bef"s, "ghba"sv) == 11);
    }

    TEST_CASE("concat")
    {
        CHECK(concat('a') == "a"sv);
        CHECK(concat("aa") == "aa"sv);
        CHECK(concat('a', "bbb", "", "bef"s, "ghba"sv) == "abbbbefghba"sv);
    }

    TEST_CASE("quoted")
    {
        CHECK(quoted('"') == "\"\"\"\""sv);
        CHECK(quoted('!') == "\"!\""sv);

        CHECK(quoted("hello") == "\"hello\""sv);
        CHECK(quoted(" abc "sv) == "\" abc \""sv);
        CHECK(quoted("\"") == "\"\"\"\""sv);
        CHECK(quoted("\"\""s) == "\"\"\"\"\"\""sv);
        CHECK(quoted("a\"b\"c"sv) == "\"a\"\"b\"\"c\""sv);
    }

    TEST_CASE("delimitedConcat")
    {
        CHECK(delimitedConcat(',', "nope") == "nope"sv);
        CHECK(delimitedConcat(',', "alpha"sv, "beta"s) == "alpha,beta"sv);
        CHECK(delimitedConcat("; "sv, "1", "2", "3", "4"sv) == "1; 2; 3; 4"sv);
    }

    TEST_CASE("delimitedQuotedConcat")
    {
        CHECK(delimitedQuotedConcat(',', "nope") == "\"nope\""sv);
        CHECK(delimitedQuotedConcat(',', "alpha"sv, "beta"s) == "\"alpha\",\"beta\""sv);
        CHECK(delimitedQuotedConcat("; "sv, "1", "2", "3", "4"sv) == "\"1\"; \"2\"; \"3\"; \"4\""sv);
        CHECK(delimitedQuotedConcat(" -- "sv, '"', "\"hekk\""sv, "aaa"sv, ""sv) == 
            "\"\"\"\" -- \"\"\"hekk\"\"\" -- \"aaa\" -- \"\""sv);
    }

}
