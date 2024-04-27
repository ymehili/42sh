/*
** EPITECH PROJECT, 2023
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** execute_background.c
*/

#include "../include/sh.h"

void make_redirection(infos_t *infos, pid_t child)
{
    setsid();
    dup2(infos->jobs->pipefd[1], STDOUT_FILENO);
    dup2(infos->jobs->pipefd[1], STDERR_FILENO);
    close(infos->jobs->pipefd[1]);
}

void redirect_into_output(infos_t *infos)
{
    fd_set read_fds;
    struct timeval timeout;

    fcntl(infos->jobs->pipefd[0], F_SETFL, O_NONBLOCK);
    FD_ZERO(&read_fds);
    FD_SET(infos->jobs->pipefd[0], &read_fds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 500;
    select(infos->jobs->pipefd[0] + 1, &read_fds, NULL, NULL, &timeout);
}
