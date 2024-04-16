/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_split_to_str
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(split_to_str, basic_test)
{
    char *split[] = {"Hello", "world!", "This", "is", "a", "test.", NULL};
    char separator = '/';
    int at_end = 1;
    char *result = split_to_str(split, at_end);

    cr_assert_not_null(result, "split_to_str() returned NULL");
    cr_assert_str_eq(result, "Hello/world!/This/is/a/test./");
}

Test(split_to_str, empty_split)
{
    char *split[] = {NULL};
    char separator = '/';
    int at_end = 0;
    char *result = split_to_str(split, at_end);

    cr_assert_not_null(result, "split_to_str() returned NULL");
    cr_assert_str_empty(result);
}
