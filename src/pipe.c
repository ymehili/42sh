/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-lucas.leclerc
** File description:
** pipe
*/

#include "../include/sh.h"

static void wait_childs(infos_t *infos)
{
    int status = 0;

    for (int i = 0; i <= infos->nb_pipe; i++) {
        wait(&status);
        infos->exit_code = status_code(status);
    }
}

void if_child(infos_t *infos, int i, int pipe_fd[2],
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    int built_in_nb = is_built_in_command(infos, infos->input_parse[0]);

    if (i != 0) {
        dup2(infos->input_fd, STDIN_FILENO);
        close(infos->input_fd);
    }
    if (i != infos->nb_pipe) {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
    handle_redirection(infos);
    if (built_in_nb != -1)
        exit(exec_built_in(infos, built_in_nb, built_in_commands));
    execve(infos->input_parse[0], infos->input_parse, infos->env);
    exec_with_path(infos);
    return_error(infos->input_parse[0], ": Command not found.\n", 1);
    exit(1);
}

int handle_pipe(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **input)
{
    int pipe_fd[2];

    for (int i = 0; i <= infos->nb_pipe; i++) {
        if (is_redirection(infos, input[i]))
            input[i] = save_redirection(infos, input[i]);
        infos->input_parse = shsplit(input[i]);
        if (i != infos->nb_pipe)
            pipe(pipe_fd);
        if (fork() == 0)
            if_child(infos, i, pipe_fd, built_in_commands);
        if (i != 0)
            close(infos->input_fd);
        if (i != infos->nb_pipe) {
            close(pipe_fd[1]);
            infos->input_fd = pipe_fd[0];
        }
    }
    wait_childs(infos);
    return 0;
}
