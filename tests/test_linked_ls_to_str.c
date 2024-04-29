/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_linked_ls_to_str
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(old_env_to_new, should_handle_empty_linked_list)
{
    infos_t infos;
    infos.env_linked_ls = NULL;

    char **new_env = old_env_to_new(&infos);
    cr_assert_null(new_env[0]);

    free(new_env);
}
