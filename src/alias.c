/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** alias
*/

#include "../include/sh.h"

static void delete_alias(infos_t *infos, alias_t *elem)
{
    if (elem->prev != NULL)
        elem->prev->next = elem->next;
    if (elem->next != NULL)
        elem->next->prev = elem->prev;
    if (elem->prev == NULL)
        infos->alias = elem->next;
    if (elem->next == NULL)
        infos->alias = NULL;
    free(elem->alias);
    free(elem->command);
    free(elem);
}

int unalias_func(infos_t *infos)
{
    alias_t *elem = infos->alias;

    if (elem == NULL)
        return 0;
    for (; elem != NULL; elem = elem->next) {
        if (my_strcmp(elem->alias, infos->input_parse[1]) == 0) {
            delete_alias(infos, elem);
            return 0;
        }
    }
    return 0;
}

void print_alias(infos_t *infos)
{
    alias_t *alias = infos->alias;

    if (alias == NULL)
        return;
    for (; alias != NULL; alias = alias->next) {
        my_putstr(alias->alias);
        my_putstr("\t");
        my_putstr(alias->command);
        my_putstr("\n");
    }
    return;
}

static char *parse_alias_command(infos_t *infos)
{
    char *args = NULL;
    char *temp = NULL;

    for (int i = 2; i < tab_len(infos->input_parse); i++) {
        if (args == NULL) {
            args = my_strdup(infos->input_parse[i]);
        } else {
            args = my_strcat(args, " ");
            args = my_strcat(args, infos->input_parse[i]);
        }
    }
    if (tab_len(infos->input_parse) > 3) {
        temp = my_strcat("(", args);
        args = my_strcat(temp, ")");
        free(temp);
    }
    return args;
}

static int search_alias_command(infos_t *infos, alias_t *new)
{
    alias_t *alias = infos->alias;

    while (alias != NULL) {
        if (strcmp(alias->alias, new->alias) == 0) {
            free(alias->command);
            alias->command = new->command;
            free(new->alias);
            free(new);
            return 0;
        }
        alias = alias->next;
    }
    return 1;
}

void add_alias(infos_t *infos)
{
    alias_t *new = my_malloc(sizeof(alias_t));

    new->alias = my_strdup(infos->input_parse[1]);
    new->command = parse_alias_command(infos);
    new->next = NULL;
    new->prev = NULL;
    if (search_alias_command(infos, new) == 0)
        return;
    if (infos->alias == NULL) {
        infos->alias = new;
        return;
    }
    infos->alias->prev = new;
    new->next = infos->alias;
    infos->alias = new;
    return;
}

static void search_alias(infos_t *infos)
{
    char *tmp = NULL;

    for (alias_t *alias = infos->alias; alias != NULL;
        alias = alias->next) {
        if (my_strcmp(alias->alias, infos->input_parse[1]) == 0) {
            tmp = delete_half_circle(alias->command);
            my_putstr(tmp);
            my_putstr("\n");
            return;
        }
    }
    return;
}

int alias_func(infos_t *infos)
{
    if (infos->input_parse[1] != NULL && infos->input_parse[2] != NULL) {
        add_alias(infos);
        return 0;
    }
    if (infos->input_parse[1] != NULL && infos->input_parse[2] == NULL) {
        search_alias(infos);
        return 0;
    }
    print_alias(infos);
    return 0;
}
