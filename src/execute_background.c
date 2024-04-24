/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** execute_background.c
*/

#include "../include/sh.h"

void make_redirection(infos_t *infos, int *pipefd, pid_t child)
{
    setsid();
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[1]);
}

void redirect_into_output(infos_t *infos, int *pipefd)
{
    char buffer[4096];
    ssize_t nbytes;
    fd_set read_fds;
    struct timeval timeout;
    int retval = 0;

    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
    FD_ZERO(&read_fds);
    FD_SET(pipefd[0], &read_fds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 500;
    retval = select(pipefd[0] + 1, &read_fds, NULL, NULL, &timeout);
    nbytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
    buffer[nbytes] = '\0';
    if (!infos->jobs->output_job) {
        infos->jobs->output_job = strdup(buffer);
        infos->jobs->finish = 1;
    }
    close(pipefd[0]);
}
