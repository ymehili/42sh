/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history_builtins2
*/

#include "../include/sh.h"

static char *all_history_args_bis(char *token, char *g_tok)
{
    token = strtok(NULL, " ");
    while (token != NULL) {
        if (g_tok == NULL) {
            g_tok = strdup(token);
        } else {
            g_tok = realloc(g_tok, strlen(g_tok) + strlen(token) + 2);
            strcat(g_tok, " ");
            strcat(g_tok, token);
        }
        token = strtok(NULL, " ");
    }
    return g_tok;
}

int all_history_args(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    char *token = strtok(my_strdup(tmp->command), " ");
    char *g_tok = NULL;

    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    g_tok = all_history_args_bis(token, g_tok);
    strn_replace(infos, g_tok, "!");
    free(g_tok);
    return -1;
}

int last_history_args(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    char *tmp_command = my_strdup(tmp->command);
    char *token = strtok(tmp_command, " ");
    char *last_token = NULL;

    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    while (token != NULL) {
        last_token = token;
        token = strtok(NULL, " ");
    }
    if (last_token != NULL) {
        strn_replace(infos, last_token, "!");
        return -1;
    }
    my_putstr("Bad ! arguments selector.\n");
    return 84;
}

static int handle_dash(char *command, int *end_id)
{
    char *dash = strchr(&command[2], '-');

    if (dash != NULL)
        *end_id = my_getnbr(dash + 1);
    return (*end_id);
}

static int handle_token(history_args_t *history_args)
{
    if (history_args->current_id >= history_args->start_id &&
        (history_args->end_id == -1 || history_args->current_id <=
        history_args->end_id)) {
        strcat(history_args->args, history_args->token);
        strcat(history_args->args, " ");
        if (history_args->end_id == -1 || history_args->current_id ==
            history_args->end_id) {
            history_args->args[my_strlen(history_args->args)] = '\0';
            strn_replace(history_args->infos, history_args->args, "!");
            return -1;
        }
    }
    return 0;
}

int n_history_args(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    char *tmp_command = my_strdup(tmp->command);
    char *token = strtok(tmp_command, " ");
    int start_id = my_getnbr(&command[2]);
    char args[256] = "";
    history_args_t history_args = {infos, token, 0, start_id, -1, args};

    handle_dash(command, &(history_args.end_id));
    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    for (history_args.current_id = 0; history_args.token != NULL;
        history_args.current_id++) {
        if (handle_token(&history_args) == -1)
            return -1;
        history_args.token = strtok(NULL, " ");
    }
    my_putstr("Bad ! arguments selector.\n");
    return 84;
}

int first_history_args(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    char *tmp_command = my_strdup(tmp->command);
    char *token = strtok(tmp_command, " ");

    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    token = strtok(NULL, " ");
    if (token != NULL) {
        strn_replace(infos, token, "!");
        return -1;
    }
    my_putstr("Bad ! arguments selector.\n");
    return 84;
}
