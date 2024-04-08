/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_get_nb_params
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(get_nb_params, basic_test)
{
    char *params[] = {"param1", "param2", "param3", NULL};
    int result = get_nb_params(params);

    cr_assert_eq(result, 3, "get_nb_params() did not return the expected number of parameters");
}

Test(get_nb_params, empty_params)
{
    char *params[] = {NULL};
    int result = get_nb_params(params);

    cr_assert_eq(result, 0, "get_nb_params() did not return 0 for empty parameters");
}
