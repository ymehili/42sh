/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** history
*/

#include "../include/sh.h"

int search_history(infos_t *infos, char *exclamation_mark, char *command)
{
    int result = 0;
    command_mapping_t history_command[] = {
        {"!!", last_history}, {"!-", n_history_before}, {"!:", n_history_args}
    };

    for (size_t i = 0; i < sizeof(history_command) /
        sizeof(command_mapping_t); i++) {
        if (my_strncmp(exclamation_mark, history_command[i].command_str,
            my_strlen(history_command[i].command_str)) == 0) {
            result = history_command[i].func(infos, command);
            return result;
        }
    }
    return 0;
}

int history(infos_t *infos, char *command)
{
    int result = 0;
    char *exclamation_mark = strchr(command, '!');

    while (exclamation_mark != NULL) {
        result = search_history(infos, exclamation_mark, command);
        if (result != 0)
            return result;
        if (my_strn_is_letter(exclamation_mark, 1)) {
            return history_with_string(infos, command);
        }
        if (my_strn_is_num(exclamation_mark, 1)) {
            return n_history(infos, command);
        }
        exclamation_mark = strchr(exclamation_mark + 1, '!');
    }
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
