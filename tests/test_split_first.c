/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_split_first
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(split_first, basic_test)
{
    char *str = "Hello world! This is a test.";
    char *separators = " ";
    char **result = split_first(str, separators);

    cr_assert_not_null(result, "split_first() returned NULL");
    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "world! This is a test.");
}

Test(split_first, no_separator_test)
{
    char *str = "NoSeparator";
    char *separators = " ";
    char **result = split_first(str, separators);

    cr_assert_not_null(result, "split_first() returned NULL");
    cr_assert_str_eq(result[0], "NoSeparator");
    cr_assert_null(result[1]);
}
