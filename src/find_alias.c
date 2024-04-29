/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** find_alias
*/

#include "../include/sh.h"

static bool is_in_set(alias_set_t *set, char *alias)
{
    for (int i = 0; i < set->count; i++) {
        if (my_strcmp(set->alias[i], alias) == 0) {
            return true;
        }
    }
    return false;
}

static void add_to_set(alias_set_t *set, char *alias)
{
    if (!is_in_set(set, alias)) {
        set->alias[set->count] = strdup(alias);
        set->count++;
    }
}

static bool find_alias_bis(alias_t *tmp, infos_t *infos, char *token,
    alias_set_t *set)
{
    char *alias_command = NULL;
    bool alias_found = false;

    while (tmp != NULL) {
        if (strcmp(tmp->alias, token) != 0) {
            tmp = tmp->next;
            continue;
        }
        if (is_in_set(set, tmp->alias))
            return false;
        add_to_set(set, tmp->alias);
        alias_command = delete_half_circle(tmp->command);
        strn_replace(infos, alias_command, token);
        alias_found = true;
        break;
    }
    return alias_found;
}

bool process_token(alias_t *tmp, infos_t *infos, char **command_copy,
    char *token)
{
    char *new_command_copy;

    if (find_alias_bis(tmp, infos, token, infos->alias_set) != true) {
        return false;
    }
    new_command_copy = strdup(infos->input);
    new_command_copy[strlen(new_command_copy) - 1] = '\0';
    free(*command_copy);
    *command_copy = new_command_copy;
    return true;
}

int find_alias(infos_t *infos, char *command)
{
    char *command_copy = strdup(command);
    char *token;
    bool alias_found;
    alias_t *tmp = infos->alias;

    infos->alias_set->count = 0;
    command_copy[strlen(command_copy) - 1] = '\0';
    do {
        token = strtok(command_copy, " ");
        alias_found = process_token(tmp, infos, &command_copy, token);
        if (alias_found == false)
            break;
        token = strtok(NULL, " ");
        if (token == NULL)
            break;
    } while (1);
    free(command_copy);
    return 0;
}
