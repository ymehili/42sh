/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history_builtins
*/

#include "../include/sh.h"

int command_with_string(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;

    memmove(&command[0], &command[1], strlen(command));
    command[strlen(command) - 1] = '\0';
    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strncmp(tmp->command, command, my_strlen(command)) == 0) {
            infos->input = NULL;
            infos->input = my_strdup(tmp->command);
            my_putstr(infos->input);
            return -1;
        }
    }
    my_putstr(command);
    my_putstr(": Event not found.\n");
    return 84;
}

int n_command_before(infos_t *infos, char *command)
{
    int id = my_getnbr(&command[2]);
    history_t *tmp = infos->history;

    if (tmp == NULL) {
        my_putnbr(1 - id);
        my_putstr(": Event not found.\n");
        return 84;
    }
    for (id = id - 1; id != 0; id--) {
        if (tmp->next == NULL) {
            my_putnbr(1 - id);
            my_putstr(": Event not found.\n");
            return 84;
        }
        tmp = tmp->next;
    }
    infos->input = NULL;
    infos->input = my_strdup(tmp->command);
    my_putstr(infos->input);
    return -1;
}

int n_command(infos_t *infos, char *command)
{
    history_t *tmp = infos->history;
    int id = my_getnbr(&command[1]);

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->id == id) {
            infos->input = NULL;
            infos->input = my_strdup(tmp->command);
            my_putstr(infos->input);
            return -1;
        }
    }
    my_putnbr(id);
    my_putstr(": Event not found.\n");
    return 84;
}

int last_command(infos_t *infos)
{
    history_t *tmp = infos->history;

    if (tmp == NULL) {
        my_putstr("0: Event not found.\n");
        return 84;
    }
    infos->input = NULL;
    infos->input = my_strdup(tmp->command);
    my_putstr(infos->input);
    return -1;
}

int history_func(infos_t *infos)
{
    history_t *tmp = infos->history;

    if (tmp == NULL)
        return 0;
    for (; tmp->next != NULL; tmp = tmp->next);
    for (; tmp != NULL; tmp = tmp->prev)
        printf("%d %s %s", tmp->id, tmp->time, tmp->command);
    return 0;
}
