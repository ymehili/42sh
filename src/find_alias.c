/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** find_alias
*/

#include "../include/sh.h"

static void find_alias_bis(alias_t *tmp, infos_t *infos, char *token,
    char *alias_command)
{
    while (tmp != NULL) {
        if (strcmp(tmp->alias, token) == 0) {
            alias_command = delete_half_circle(tmp->command);
            strn_replace(infos, alias_command, token);
            tmp = infos->alias;
        }
        tmp = tmp->next;
    }
}

int find_alias(infos_t *infos, char *command)
{
    char *command_copy = strdup(command);
    command_copy[strlen(command_copy) - 1] = '\0';
    char *token = strtok(command_copy, " ");
    alias_t *tmp = infos->alias;
    char *alias_command = NULL;

    while (token != NULL) {
        tmp = infos->alias;
        find_alias_bis(tmp, infos, token, alias_command);
        token = strtok(NULL, " ");
    }
    free(command_copy);
    return 0;
}
