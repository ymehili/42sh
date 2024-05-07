/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** fg_command.c
*/

#include "../include/sh.h"

static int wait_fg_jobs(infos_t *infos, job_t *my_job)
{
    int status = 0;

    write(1, my_job->command, strlen(my_job->command));
    write(1, "\n", 1);
    signal(SIGTSTP, SIG_DFL);
    waitpid(my_job->pid, &status, WUNTRACED);
    delete_jobs(infos, my_job);
    return 0;
}

static int start_first_job(infos_t *infos, char **all_command, int i)
{
    for (int t = 0; all_command[i][t] != '\0'; t++) {
        if (is_not_num(all_command[i][t]) == 0) {
            write(1, "fg: No such job.\n", 17);
            return 1;
        }
    }
    return (wait_fg_jobs(infos, infos->jobs));
}

static int start_fg(infos_t *infos, char **all_command, int i)
{
    int my_pos = 0;

    for (int t = 0; all_command[i][t] != '\0'; t++) {
        if (is_not_num(all_command[i][t]) == 0) {
            write(1, "fg: No such job.\n", 17);
            return 1;
        }
    }
    my_pos = my_getnbr(all_command[i]);
    for (job_t *my_job = infos->first_job; my_job != NULL;
        my_job = my_job->next) {
        if (my_job->pos == my_pos)
            return (wait_fg_jobs(infos, my_job));
    }
    write(1, "fg: No current job.\n", 20);
    return 1;
}

int fg_func(infos_t *infos)
{
    char *command = my_strdup(infos->input);
    char **all_command = NULL;

    command += 2;
    all_command = split(command, " \n");
    if (all_command[1] == NULL)
        return (wait_fg_jobs(infos, infos->jobs));
    for (int i = 0; all_command[i]; i++) {
        if (all_command[i][0] == '%') {
            all_command[i] ++;
            start_fg(infos, all_command, i);
        }
        if (all_command[i][0] != '%') {
            start_first_job(infos, all_command, i);
        }
    }
    return 0;
}
