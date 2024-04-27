/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** status_jobs.c
*/

#include "../include/sh.h"

static void jobs_finish(infos_t *infos, job_t *job)
{
    char *buffer = my_malloc(sizeof(char) * 4096);
    ssize_t nbytes;

    while ((nbytes = read(job->pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[nbytes] = '\0';
        if (job->output_job == NULL) {
            job->output_job = strdup(buffer);
        } else {
            char *new_output = malloc(strlen(job->output_job) + nbytes + 1);
            strcpy(new_output, job->output_job);
            strcat(new_output, buffer);
            free(job->output_job);
            job->output_job = new_output;
        }
    }
    if (job->output_job != NULL)
        my_putstr(job->output_job);
}

static void print_jobs_result(infos_t *infos, job_t *job)
{
    my_putstr("[");
    my_putnbr(job->pos);
    my_putstr("] ");
    my_putnbr(job->pid);
    my_putstr("\t\t[DONE] ");
    my_putstr(job->command);
    my_putstr("\n");
}

static void delete_jobs(infos_t *infos, job_t *job)
{
    if (job->prev == NULL) {
        infos->first_jobs = job->next;
        if (job->next != NULL) {
            job->next->prev = NULL;
        }
    } else {
        job->prev->next = job->next;
        if (job->next != NULL) {
            job->next->prev = job->prev;
        }
    }
}

static void finish_jobs(infos_t *infos, job_t *job, int status)
{
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        jobs_finish(infos, job);
        close(job->pipefd[0]);
        print_jobs_result(infos, job);
        delete_jobs(infos, job);
    }
}

void check_jobs_status(infos_t *infos)
{
    int status;
    job_t *job = infos->first_jobs;

    while (job != NULL) {
        if (waitpid(job->pid, &status, WNOHANG) > 0)
            finish_jobs(infos, job, status);
        job = job->next;
    }
}
