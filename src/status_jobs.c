/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** status_jobs.c
*/

#include "../include/sh.h"

void display_output_job(infos_t *infos, job_t *job)
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
        display_output_job(infos, job);
        close(job->pipefd[0]);
        print_jobs_result(infos, job, status);
        delete_jobs(infos, job);
    } 
}

void check_jobs_end(infos_t *infos)
{
    int status;
    job_t *job = infos->first_jobs;

    while (job != NULL) {
            // printf("\nDANS LE CODE je check le (%s)", job->command);
            if (waitpid(job->pid, &status, WNOHANG) > 0)
                finish_jobs(infos, job, status);
        job = job->next;
    }
}

void *check_jobs_status(void *arg)
{
    infos_t *infos = (infos_t *)arg;
    int status;
    job_t *job;

    while (1) {
        job = infos->first_jobs;
        while (job != NULL) {
            // printf("\nDANS LE THREAD je check le (%s)", job->command);
            if (waitpid(job->pid, &status, WNOHANG) > 0) {
                printf("job fini\n");
                finish_jobs(infos, job, status);
            }
            job = job->next;
        }
        sleep(1);
    }
    free(job);
    return NULL;
}