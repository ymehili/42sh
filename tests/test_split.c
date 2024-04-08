/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_split
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(split, basic_test)
{
    char *str = "Hello world! This is a test.";
    char *separators = " ";
    char **result = split(str, separators);

    cr_assert_not_null(result, "split() returned NULL");
    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "world!");
    cr_assert_str_eq(result[2], "This");
    cr_assert_str_eq(result[3], "is");
    cr_assert_str_eq(result[4], "a");
    cr_assert_str_eq(result[5], "test.");
    cr_assert_null(result[6]);
}

Test(split, empty_string)
{
    char *str = "";
    char *separators = " ";
    char **result = split(str, separators);

    cr_assert_not_null(result, "split() returned NULL");
    cr_assert_null(result[0]);
    cr_assert_null(result[1]);
}
