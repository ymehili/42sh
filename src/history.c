/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history
*/

#include "../include/sh.h"

int history_bis(infos_t *infos, char *command)
{
    if (command[0] != '!')
        return 1;
    if (command[0] == '!' && command[1] == '!')
        return last_command(infos);
    if (command[0] == '!' && my_strn_is_num(command, 1) == 1)
        return n_command(infos, command);
    if (command[0] == '!' && command[1] == '-' &&
        my_strn_is_num(command, 2) == 1) {
        printf("Réexécute la n-ième commande précédente.\n");
        return -1;
    }
    if (command[0] == '!' && my_strn_is_letter(command, 1)) {
        printf("Réexécute la dernière commande commençant par string.\n");
        return -1;
    }
    return 0;
}

int history(infos_t *infos, char *command)
{
    int ret = history_bis(infos, command);

    if (ret == -1)
        return -1;
    if (ret == 84)
        return 84;
    if (ret == 1)
        return 1;
    if (command[0] == '!' && command[1] == ':' && my_strn_is_num(command, 2)) {
        printf("Accède au n-ième argument de la dernière commande.\n");
        return -1;
    }
    if (command[0] == '!' && command[1] == '$') {
        printf("Référence le dernier argument de la dernière commande.\n");
        return -1;
    }
    memmove(&command[0], &command[1], strlen(command));
    my_putstr(command);
    my_putstr(": Event not found.\n");
    return 84;
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

history_t *add_to_history(infos_t *infos, char *command)
{
    history_t *new = my_malloc(sizeof(history_t));
    time_t clock = time(NULL);
    struct tm *timing = localtime(&clock);

    new->time = my_malloc(6);
    strftime(new->time, 6, "%H:%M", timing);
    new->command = my_strdup(command);
    new->next = infos->history;
    if (infos->history != NULL) {
        infos->history->prev = new;
        new->id = infos->history->id + 1;
    } else {
        new->prev = NULL;
        new->id = 1;
    }
    return new;
}
