/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** test_strsplit
*/

#include "../include/sh.h"
#include <criterion/criterion.h>


Test(strsplit, should_split_string_by_space)
{
    char **result = strsplit("Hello world", " ");

    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "world");
    free(result);
}

Test(strsplit, should_split_string_by_comma)
{
    char **result = strsplit("apple,banana,carrot", ",");

    cr_assert_str_eq(result[0], "apple");
    cr_assert_str_eq(result[1], "banana");
    cr_assert_str_eq(result[2], "carrot");
    free(result);
}

Test(strsplit, should_handle_empty_string)
{
    char **result = strsplit("", ",");

    cr_assert_null(result[0]);
    free(result);
}

Test(strsplit, should_handle_no_delimiter_in_string)
{
    char **result = strsplit("Hello world", ",");

    cr_assert_str_eq(result[0], "Hello world");
    free(result);
}
