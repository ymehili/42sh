/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_strn_replace
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(remove_line_return, should_remove_line_return)
{
    infos_t infos;
    infos.input = strdup("Hello\n");
    remove_line_return(&infos);
    cr_assert_str_eq(infos.input, "Hello\n");
    free(infos.input);
}

Test(remove_line_return, should_not_remove_non_line_return)
{
    infos_t infos;
    infos.input = strdup("Hello");
    remove_line_return(&infos);
    cr_assert_str_eq(infos.input, "Hello\n");
    free(infos.input);
}

Test(strn_replace, should_replace_substring)
{
    infos_t infos;
    infos.input = strdup("Hello world");
    strn_replace(&infos, "everyone", "world");
    cr_assert_str_eq(infos.input, "Hello everyone\n");
    free(infos.input);
}

Test(strn_replace, should_not_replace_if_substring_not_found)
{
    infos_t infos;
    infos.input = strdup("Hello world");
    strn_replace(&infos, "everyone", "universe");
    cr_assert_str_eq(infos.input, "Hello world\n");
    free(infos.input);
}
