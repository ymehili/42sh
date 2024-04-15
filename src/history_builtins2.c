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
    strn_replace(infos, g_tok);
    my_putstr(infos->input);
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
        strn_replace(infos, last_token);
        my_putstr(infos->input);
        return -1;
    }
    my_putstr("Bad ! arguments selector.\n");
}

int n_history_args(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    char *tmp_command = my_strdup(tmp->command);
    char *token = strtok(tmp_command, " ");
    int id = my_getnbr(&command[2]);

    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    for (int current_id = 0; token != NULL; current_id++) {
        if (current_id == id) {
            strn_replace(infos, token);
            my_putstr(infos->input);
            my_putstr("\n");
            return -1;
        }
        token = strtok(NULL, " ");
    }
    my_putstr("Bad ! arguments selector.\n");
}
