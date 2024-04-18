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

static void free_env(infos_t *infos)
{
    env_var_t *tmp = infos->env_linked_ls;
    env_var_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->name);
        free(tmp->val);
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

void free_input_parse(infos_t *infos)
{
    if (infos->input_parse != NULL) {
        for (int i = 0; infos->input_parse[i] != NULL; i++) {
            free(infos->input_parse[i]);
        }
        free(infos->input_parse);
    }
}

void free_all(infos_t *infos)
{
    free(infos->env);
    free(infos->last_pwd);
    free(infos->line_cwd);
    free_env(infos);
    free_var_ls(infos);
    free(infos->actual_path);
    free(infos->input);
    free_input_parse(infos);
    free(infos->built_in_command_name);
    free(infos->out_file_name);
    free(infos->in_file_name);
    free_history(infos);
    free_alias(infos);
    free(infos);
}
