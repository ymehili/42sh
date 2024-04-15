/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history_builtins2
*/

#include "../include/sh.h"

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
            return -1;
        }
        token = strtok(NULL, " ");
    }
    my_putstr("Bad ! arguments selector.\n");
}
