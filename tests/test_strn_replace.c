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
    char str[] = "ls !:1";
    infos_t *infos = my_malloc(sizeof(infos_t));
    infos->input = str;

    strn_replace(infos, "-l");
    cr_assert_str_eq(infos->input, "ls -l");
    free(infos);
}

Test(strn_replace, should_replace_substring)
{
    char str[] = "ls :1";
    infos_t *infos = my_malloc(sizeof(infos_t));
    infos->input = str;

    strn_replace(infos, "-l");
    cr_assert_str_eq(infos->input, "ls :1");

    free(infos);
}
