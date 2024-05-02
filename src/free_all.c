/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** free_all
*/

#include "../include/sh.h"

static void free_alias(infos_t *infos)
{
    alias_t *tmp = infos->alias;
    alias_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->alias);
        free(tmp->command);
        free(tmp);
        tmp = next;
    }
}

static void free_var_ls(infos_t *infos)
{
    env_var_t *tmp = infos->var_ls;
    env_var_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->name);
        free(tmp->val);
        free(tmp);
        tmp = next;
    }
}

static void free_history(infos_t *infos)
{
    history_t *tmp = infos->history;
    history_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->time);
        free(tmp->command);
        free(tmp);
        tmp = next;
    }
}

int free_all(infos_t *infos)
{
    int exit_num = 0;

    exit_num = infos->exit_code;
    free_var_ls(infos);
    free(infos->actual_path);
    free(infos->input);
    free(infos->built_in_command_name);
    free(infos->out_file_name);
    free(infos->in_file_name);
    free_history(infos);
    free_alias(infos);
    free(infos);
    return exit_num;
}
