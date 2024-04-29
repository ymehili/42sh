/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_alias
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(unalias_func, should_remove_alias)
{
    infos_t infos;
    alias_t *alias = malloc(sizeof(alias_t));
    alias->alias = strdup("alias");
    alias->command = strdup("command");
    alias->next = NULL;
    alias->prev = NULL;
    infos.alias = alias;
    infos.input_parse = malloc(sizeof(char *) * 2);
    infos.input_parse[0] = strdup("unalias");
    infos.input_parse[1] = strdup("alias");
    unalias_func(&infos);
    cr_assert_null(infos.alias);
}

Test(unalias_func, should_not_remove_alias)
{
    infos_t infos;
    alias_t *alias = malloc(sizeof(alias_t));
    alias->alias = strdup("alias");
    alias->command = strdup("command");
    alias->next = NULL;
    alias->prev = NULL;
    infos.alias = alias;
    infos.input_parse = malloc(sizeof(char *) * 2);
    infos.input_parse[0] = strdup("unalias");
    infos.input_parse[1] = strdup("alias2");
    unalias_func(&infos);
    cr_assert_not_null(infos.alias);
}

Test(print_alias, should_print_alias)
{
    infos_t infos;
    alias_t *alias = malloc(sizeof(alias_t));
    alias->alias = strdup("alias");
    alias->command = strdup("command");
    alias->next = NULL;
    alias->prev = NULL;
    infos.alias = alias;
    print_alias(&infos);
}
