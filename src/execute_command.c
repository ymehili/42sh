/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** execute_command
*/

#include "../include/sh.h"

static int launch_command(infos_t *infos, int *pipefd)
{
    // if (infos->is_a_job == 1) {
    //     my_putstr("[");
    //     my_putnbr(infos->jobs->pos);
    //     my_putstr("] ");
    //     // redirect_into_output(infos, pipefd);
    // }
    handle_redirection(infos);
    execve(infos->input_parse[0], infos->input_parse, infos->env);
    exec_with_path(infos);
    return_error(infos->input_parse[0], ": Command not found.\n", 1);
    exit(1);
}

void check_jobs_status(infos_t *infos)
{
    int status;
    job_t *job = infos->first_jobs;
    pid_t result;

    while (job != NULL) {
        if (job->command != NULL) {
            result = waitpid(job->pid, &status, WNOHANG);
            if (result > 0) {
                if (WIFEXITED(status) || WIFSIGNALED(status)) {
                    job->finish = 1;
                    my_putstr("[");
                    my_putnbr(job->pos);
                    my_putstr("] ");
                    my_putnbr(job->pid);
                    my_putstr("\t\t[DONE] ");
                    my_putstr(job->command);
                    my_putstr("\n");
                }
            }
        }
        job = job->next;
    }
}


static int end_of_execve(infos_t *infos, int *pipefd, pid_t child, int status)
{
    close(pipefd[1]);
    if (infos->is_a_job == 1) {
        redirect_into_output(infos, pipefd);
        start_a_job(infos);
    }
    else
        waitpid(child, &status, 0);
    check_jobs_status(infos);
    return status_code(status);
}

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

int execute_command(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_t *))
{
    int status = 0;
    pid_t child;
    int pipefd[2];
    int built_in_nb = is_built_in_command(infos, infos->input_parse[0]);

    if (built_in_nb != -1)
        return exec_built_in(infos, built_in_nb, built_in_commands);
    pipe(pipefd);
    child = fork();
    if (child < 0)
        return 84;
    else if (child == 0) {
        close(pipefd[0]);
        if (infos->is_a_job == 1) {
            infos->jobs->pid = getpid();
            my_putstr("[");
            my_putnbr(infos->jobs->pos);
            my_putstr("] ");
            my_putnbr(infos->jobs->pid);
            my_putstr("\n");
            make_redirection(infos, pipefd, child);
        }
        launch_command(infos, pipefd);
    }
    if (infos->is_a_job == 1) {
        infos->jobs->pid = child;
    }
    return end_of_execve(infos, pipefd, child, status);
}
