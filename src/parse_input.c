/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** parse_input
*/

#include "../include/sh.h"

static int handle_and(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **and_commands)
{
    for (int i = 0; and_commands[i] != NULL; i++) {
        infos->input = my_strdup(and_commands[i]);
        process_input(infos, built_in_commands);
        if (infos->exit_code != 0)
            return 1;
    }
    return 0;
}

static int handle_or(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **or_commands)
{
    for (int i = 0; or_commands[i] != NULL; i++) {
        infos->input = my_strdup(or_commands[i]);
        process_input(infos, built_in_commands);
        if (infos->exit_code == 0)
            return 0;
    }
    return 1;
}

static int handle_and_or_pipe_commands(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **commands, int i)
{
    char *command = my_strdup(commands[i]);
    char **and_commands = strsplit(command, "&&");
    char **or_commands = strsplit(command, "||");
    char **pipe_commands = splitforpipe(command, "|");
    int ret = 0;

    if (pipe_commands[1] != NULL && check_pipe(infos, command)){
        handle_pipe(infos, built_in_commands, pipe_commands);
        ret = 1;
    }
    if (and_commands[1] != NULL){
        handle_and(infos, built_in_commands, and_commands);
        ret = 1;
    }
    if (or_commands[1] != NULL){
        handle_or(infos, built_in_commands, or_commands);
        ret = 1;
    }
    return ret;
}

static void handle_redirection_and_execution(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **commands, int i)
{
    if (is_redirection(infos, commands[i]))
        commands[i] = save_redirection(infos, commands[i]);
    infos->input_parse = split(commands[i], " \t\n");
    if (infos->input_parse[0] != NULL)
        infos->exit_code = execute_command(infos, built_in_commands);
}

int parse_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    char **commands = split(infos->input, ";");
    int pipeandor = 0;

    for (int i = 0; commands[i] != NULL; i++) {
        pipeandor = handle_and_or_pipe_commands(infos, built_in_commands,
            commands, i);
        if (pipeandor == 0)
            handle_redirection_and_execution(infos, built_in_commands,
                commands, i);
    }
    return 0;
}
