/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** command_jobs.c
*/

#include "../include/sh.h"


void wait_jobs(infos_t *infos, int my_pos)
{
    int status;
    job_t *job = infos->first_jobs;

    while (job != NULL) {
        if (job->pos == my_pos) {
                waitpid(job->pid, &status, 0);
                display_output_job(infos, job);
        }
        job = job->next;
    }
}

int fg_func(infos_t *infos)
{
    char *command = my_strdup(infos->input);
    char **all_command = NULL;
    int my_pos = 0;

    command += 3;
    all_command = split(command, " ");
    for (int i = 0; all_command[i]; i++) {
        if (all_command[i][0] == '%') {
            all_command[i] ++;
            printf("ma commande (%s)\n", all_command[i]);
            for (int t = 0; all_command[i][t] != '\0'; t++) {
                if (is_not_num(all_command[i][t]) == 0) {
                    write (1, "fg: No such job.\n", 17);
                    return 1;
                }
            }
            my_pos = my_getnbr(all_command[i]);
            for (job_t *my_job = infos->first_jobs; my_job->next != NULL; my_job = my_job->next) {
                if (my_job->pos == my_pos){
                    write(1, my_job->command, strlen(my_job->command));
                    my_putstr("\n");
                    wait_jobs(infos, my_pos);
                }
            }
        }
    }
    return 0;
}
