/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** bg_command.c
*/

#include "../include/sh.h"

static void remove_backslash(job_t **my_job)
{
    char *command = (*my_job)->command;

    for (int i = 0; command[i]; i++) {
        if (command[i] == '/')
            command[i] = ' ';
    }
}

static int restart_bg_jobs(infos_t *infos, job_t *my_job)
{
    if (my_job != NULL) {
        my_putstr("[");
        my_putnbr(my_job->pos);
        my_putstr("]\t");
        remove_backslash(&my_job);
        write(1, my_job->command, strlen(my_job->command));
        write(1, "&\n", 2);
        kill(my_job->pid, SIGCONT);
    }
    return 0;
}

static int start_first_job(infos_t *infos, char **all_command, int i)
{
    for (int t = 0; all_command[i][t] != '\0'; t++) {
        if (is_not_num(all_command[i][t]) == 0) {
            write(1, "bg: No such job.\n", 17);
            return 1;
        }
    }
    return (restart_bg_jobs(infos, infos->first_job));
}

static int start_bg(infos_t *infos, char **all_command, int i)
{
    int my_pos = 0;

    for (int t = 0; all_command[i][t] != '\0'; t++) {
        if (is_not_num(all_command[i][t]) == 0) {
            write(1, "bg: No such job.\n", 17);
            return 1;
        }
    }
    my_pos = my_getnbr(all_command[i]);
    for (job_t *my_job = infos->first_job; my_job != NULL;
        my_job = my_job->next) {
        if (my_job->pos == my_pos)
            return (restart_bg_jobs(infos, my_job));
    }
    write(1, "bg: No current job.\n", 20);
    return 1;
}

int bg_func(infos_t *infos)
{
    char *command = my_strdup(infos->input);
    char **all_command = NULL;

    all_command = split(command, " \n");
    if (all_command[1] == NULL) {
        return (restart_bg_jobs(infos, infos->first_job));
    }
    for (int i = 1; all_command[i]; i++) {
        if (all_command[i][0] == '%') {
            all_command[i] ++;
            start_bg(infos, all_command, i);
        } else {
            start_first_job(infos, all_command, i);
        }
    }
    return 0;
}
