/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** status_jobs.c
*/

#include "../include/sh.h"

static void print_jobs_result(infos_t *infos, job_t *job, int status)
{
    int exit_status = WEXITSTATUS(status);

    my_putstr("[");
    my_putnbr(job->pos);
    my_putstr("]");
    if (exit_status == 0)
        my_putstr("  + Done\t\t\t\t");
    else {
        my_putstr("  + Exit 1\t\t\t\t");
        infos->jobs->pos = infos->jobs->pos - 1;
    }
    my_putstr(job->command);
    my_putstr("\n");
}

void delete_jobs(infos_t *infos, job_t *job)
{
    if (job->prev == NULL) {
        infos->first_job = job->next;
        if (job->next != NULL) {
            job->next->prev = NULL;
        }
    } else {
        job->prev->next = job->next;
        if (job->next != NULL) {
            job->next->prev = job->prev;
            return;
        }
    job->prev->next = NULL;
    job = job->prev;
    }
}

void finish_jobs(infos_t *infos, job_t *job, int status)
{
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        print_jobs_result(infos, job, status);
        delete_jobs(infos, job);
    }
}

void check_jobs_end(infos_t *infos)
{
    int status;
    job_t *job = infos->first_job;

    while (job != NULL) {
            if (waitpid(job->pid, &status, WNOHANG) > 0)
                finish_jobs(infos, job, status);
        job = job->next;
    }
}
