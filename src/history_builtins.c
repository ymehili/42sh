/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history_builtins
*/

#include "../include/sh.h"

int n_command(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    int id = my_getnbr(&command[1]);

    printf("Réexécute la n-ième commande.\n");
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->id == id) {
            infos->input = NULL;
            infos->input = my_strdup(tmp->command);
            my_putstr(infos->input);
            return -1;
        }
    }
    my_putnbr(id);
    my_putstr(": Event not found\n");
    return 84;
}

int last_command(infos_t *infos)
{
    history_t *tmp = infos->history;

    if (tmp == NULL) {
        my_putstr("0: Event not found\n");
        return 84;
    }
    infos->input = NULL;
    infos->input = my_strdup(tmp->command);
    my_putstr(infos->input);
    return -1;
}
