/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** backtick
*/

#include "../include/sh.h"

char *backtick_red(infos_t *infos, int pipe_fd[2])
{
    char buffer[BUFFER_SIZE];
    char *output;
    int size = 0;

    close(pipe_fd[1]);
    size = read(pipe_fd[0], buffer, BUFFER_SIZE);
    close(pipe_fd[0]);
    if (size < 0)
        return NULL;
    output = my_malloc(sizeof(char) * size + 1);
    return my_strncpy(output, buffer, size);
}

void backtick_redirection(infos_t *infos, int pipe_fd[2])
{
    if (infos->output_type == 0 && infos->is_backtick) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
}

void replace_backtick(infos_t *infos,
int (*built_in_commands[NB_BUILT_IN])(infos_t *), int i, int j)
{
    char *cmd = my_strncpy(my_malloc(sizeof(char) * (j - i + 1)),
        &infos->input[i + 1], j - i - 1);

    cmd[j - i - 1] = '\n';
    cmd[j - i] = '\0';
    infos->input_tmp_backtick = infos->input;
    infos->input = cmd;
    infos->is_backtick = 1;
    if (process_input(infos, built_in_commands) == 84 || infos->exit_code != 0)
        infos->input = str_insert_and_replace(infos->input_tmp_backtick,
        "", i, j + 1);
    infos->is_backtick = 0;
    infos->input = str_insert_and_replace(infos->input_tmp_backtick,
        infos->backtick_output, i, j + 1);
}

static int backtick_bis(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), int i)
{
    int j;

    for (j = i + 1; infos->input[j] != '`'; j++) {
        if (infos->input[j] == '\0' || infos->input[j] == '"' ||
            infos->input[j] == '\'') {
            my_putstr("Unmatched '`'.\n");
            infos->input = str_insert_and_replace(infos->input_tmp_backtick,
            "", i, j);
            infos->exit_code = 1;
            return 1;
        }
    }
    replace_backtick(infos, built_in_commands, i, j);
    return 0;
}

int backtick(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    int output = 0;

    for (int i = 0; infos->input[i] != '\0' && output == 0; i++) {
        if (infos->input[i] == '`') {
            output = backtick_bis(infos, built_in_commands, i);
        }
    }
    return output;
}
