/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** file_rc
*/

#include "../include/sh.h"

char *open_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    char *buffer;
    struct stat st;
    int size;

    if (fd == -1)
        return NULL;
    stat(file_name, &st);
    buffer = my_malloc(sizeof(char) * (st.st_size + 1));
    if (buffer == NULL)
        return NULL;
    size = read(fd, buffer, st.st_size);
    if (size == -1) {
        free(buffer);
        return NULL;
    }
    buffer[size] = '\0';
    return buffer;
}

void reset_history(infos_t *infos)
{
    history_t *tmp = infos->history;
    history_t *next;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->command);
        free(tmp->time);
        free(tmp);
        tmp = next;
    }
    infos->history = NULL;
}

void file_rc_bis(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char *line)
{
    infos->input = NULL;
    infos->input = strdup(line);
    infos->input = my_strcat(infos->input, "\n");
    process_input(infos, built_in_commands);
}

int file_rc(infos_t *infos, int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    char *rc_file = open_file("42shrc");
    char *rc_file_copy;
    char *line;
    char *saveptr;

    if (rc_file == NULL)
        return 84;
    rc_file_copy = strdup(rc_file);
    line = strtok_r(rc_file_copy, "\n", &saveptr);
    while (line != NULL) {
        if (line[0] != '\0' && line[0] != '#' && line[0] != '\n') {
            file_rc_bis(infos, built_in_commands, line);
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }
    reset_history(infos);
    free(rc_file);
    free(rc_file_copy);
    return 0;
}
