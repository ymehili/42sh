/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** execute_command
*/

#include "../include/sh.h"

int is_built_in_command(infos_t *infos, char *command)
{
    for (int i = 0; i < NB_BUILT_IN; i++) {
        if (my_strncmp(command,
            infos->built_in_command_name[i],
            my_strlen(command)) == 0 &&
            my_strncmp(command,
            infos->built_in_command_name[i],
            my_strlen(infos->built_in_command_name[i])) == 0)
            return i;
    }
    return -1;
}

int exec_built_in(infos_t *infos, int built_in_nb,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_t *))
{
    if (built_in_nb == 3) {
        my_putstr("exit\n");
        exit(0);
    }
    return built_in_commands[built_in_nb](infos);
}

int exec_with_path(infos_t *infos)
{
    char *path_val = get_env_var(infos->env, "PATH");
    char **path_val_ls;

    if (my_char_isalpha(infos->input_parse[0][0]) == 0 || path_val == NULL)
        return 0;
    path_val_ls = split(path_val, ":");
    for (int i = 0; path_val_ls[i] != NULL; i++) {
        if (my_strcmp(path_val_ls[i], "/") == 0)
            continue;
        execve(my_strcat(my_strcat(path_val_ls[i], "/"),
            infos->input_parse[0]), infos->input_parse, infos->env);
    }
    return 0;
}

int status_code(int status)
{
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGSEGV) {
            my_putstr("Segmentation fault\n");
            return 1;
        }
        return WEXITSTATUS(status);
    }
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 126) {
            my_putstr("Wrong architecture\n");
            return 1;
        }
    }
    return WEXITSTATUS(status);
}

static void child_execute_command(infos_t *infos, int pipe_fd[2])
{
    handle_redirection(infos, pipe_fd);
    execve(infos->input_parse[0], infos->input_parse, infos->env);
    exec_with_path(infos);
    return_error(infos, infos->input_parse[0], ": Command not found.\n", 1);
    exit(1);
}

static void check_suspend_command(infos_t *infos, pid_t child, int status)
{
    if (WSTOPSIG(status) == SIGTSTP) {
        write(1, "\nSuspended\n", 11);
        start_a_job(infos);
        infos->jobs->pid = child;
        infos->jobs->command = split_to_str(infos->input_parse, 1);
    }
}

static int execute_job(infos_t *infos, pid_t child, int status)
{
    if (infos->is_a_job == 1) {
        infos->jobs->pid = child;
        my_putstr("[");
        my_putnbr(infos->jobs->pos);
        my_putstr("] ");
        my_putnbr(infos->jobs->pid);
        my_putstr("\n");
        infos->is_a_job = 0;
    } else {
        waitpid(child, &status, WUNTRACED);
        check_suspend_command(infos, child, status);
    }
    return status_code(status);
}

int execute_command(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_t *))
{
    int status = 0;
    pid_t child;
    int built_in_nb = is_built_in_command(infos, infos->input_parse[0]);
    int pipe_fd[2];

    if (infos->is_backtick)
        pipe(pipe_fd);
    if (built_in_nb != -1)
        return exec_built_in(infos, built_in_nb, built_in_commands);
    signal(SIGTSTP, SIG_IGN);
    child = fork();
    if (child < 0)
        return 84;
    else if (child == 0) {
        signal(SIGTSTP, SIG_DFL);
        child_execute_command(infos, pipe_fd);
    }
    if (infos->is_backtick)
        infos->backtick_output = backtick_red(infos, pipe_fd);
    return execute_job(infos, child, status);
}
