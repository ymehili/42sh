/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** jobs.c
*/

#include "../include/sh.h"

void start_a_job(infos_t *infos)
{
    job_t *new_job = my_malloc(sizeof(job_t));
    job_t *current_job = my_malloc(sizeof(job_t));

    new_job->output_job = NULL;
    new_job->finish = 0;
    new_job->command = NULL;
    new_job->next = NULL;
    if (infos->jobs == NULL) {
        new_job->prev = NULL;
        new_job->pos = 1;
        infos->jobs = new_job;
        infos->first_jobs = new_job;
    } else {
        current_job = infos->jobs;
        while (current_job->next != NULL)
            current_job = current_job->next;
        current_job->next = new_job;
        new_job->prev = current_job;
        new_job->pos = current_job->pos + 1;
        infos->jobs = new_job;
    }
}

static char *allocate_and_copy(char *source, int start, int length)
{
    char *result = my_malloc(sizeof(char) * (length + 1));

    strncpy(result, &source[start], length);
    result[length] = '\0';
    return result;
}

static int find_separator(char *str, char *separators)
{
    int i = 0;

    while (str[i] != '\0') {
        if (strchr(separators, str[i]) != NULL) {
            return i;
        }
        i++;
    }
    return -1;
}

char **split_once(char *str, char *separators)
{
    char **result = my_malloc(sizeof(char *) * 3);
    int separator = find_separator(str, separators);

    if (separator != -1) {
        result[0] = allocate_and_copy(str, 0, separator);
        result[1] = allocate_and_copy(str, separator + 1,
                    strlen(str) - separator - 1);
    } else {
        result[0] = strdup(str);
        result[1] = NULL;
    }
    result[2] = NULL;
    return result;
}

void realloc_command(infos_t *infos, char ***command, int i,
    char **new_command)
{
    int len_command = 0;

    for (; (*command)[len_command]; len_command++);
    (*command) = realloc(*command, sizeof(char *) * (len_command + 2));
    memmove((*command) + i + 2, (*command) + i + 1,
        sizeof(char *) * (len_command - i));
    (*command)[i] = new_command[0];
    (*command)[i + 1] = new_command[1];
    (*command)[len_command + 1] = NULL;
    infos->is_a_job = 1;
    infos->jobs->command = my_strdup((*command)[i]);
    if (infos->jobs->prev == NULL)
        infos->jobs->pos = 1;
    return;
}

void check_jobs(infos_t *infos, char ***command, int i)
{
    char **new_command = split_once((*command)[i], "&");

    if (new_command[1] != NULL)
        return realloc_command(infos, command, i, new_command);
    for (int t = 0; (*command)[i][t + 1] != '\0'; t++)
        if ((*command)[i][t] == '&') {
            infos->is_a_job = 1;
            infos->jobs->command = my_strdup((*command)[i]);
        }
    free((*command)[i]);
    (*command)[i] = new_command[0];
    return;
}
