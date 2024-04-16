/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** mysh
*/
#include "../include/sh.h"

int return_error(char *name, char *str, int code)
{
    write(2, name, my_strlen(name));
    write(2, str, my_strlen(str));
    return code;
}

infos_t *init_infos(char **env)
{
    infos_t *infos = my_malloc(sizeof(infos_t));

    infos->input = my_malloc(sizeof(char) * 32);
    infos->env = env;
    infos->history = NULL;
    infos->env_linked_ls = env_to_linked_ls(env);
    infos->built_in_command_name = my_malloc(
        sizeof(char *) * (NB_BUILT_IN + 1));
    infos->built_in_command_name[0] = my_strdup("cd");
    infos->built_in_command_name[1] = my_strdup("setenv");
    infos->built_in_command_name[2] = my_strdup("unsetenv");
    infos->built_in_command_name[3] = my_strdup("exit");
    infos->built_in_command_name[4] = my_strdup("env");
    infos->built_in_command_name[5] = my_strdup("history");
    infos->built_in_command_name[6] = my_strdup("set");
    infos->exit_code = 0;
    infos->input_fd = STDIN_FILENO;
    infos->run = 1;
    return infos;
}

void free_last_command(char **last_command)
{
    if (last_command == NULL)
        return;
    for (int i = 0; last_command[i] != NULL; i++) {
        free(last_command[i]);
    }
    free(last_command);
}

static int check_pipe_2(char **pipe_commands)
{
    char *tmp;
    int nb = 0;

    for (int i = 0; pipe_commands[i] != NULL; i++) {
        tmp = split(pipe_commands[i], " \t\n")[0];
        if (tmp == NULL || tmp[0] == '\0')
            break;
        nb++;
    }
    return nb;
}

static int check_pipe(infos_t *infos, char *input)
{
    int nb = 0;
    char **pipe_commands = split(input, "|");

    infos->nb_pipe = 0;
    for (int i = 0; input[i] != '\0'; i++)
        if (input[i] == '|')
            infos->nb_pipe++;
    if (infos->nb_pipe == 0)
        return 0;
    nb = check_pipe_2(pipe_commands);
    if (nb != infos->nb_pipe + 1) {
        my_putstr("Invalid null command.\n");
        infos->exit_code = 1;
        return 1;
    }
    return 0;
}

static int parse_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    char **commands = split(infos->input, ";");
    char **pipe_commands;

    for (int i = 0; commands[i] != NULL; i++) {
        pipe_commands = split(commands[i], "|");
        if (check_pipe(infos, commands[i]))
            continue;
        if (pipe_commands[1] != NULL) {
            handle_pipe(infos, built_in_commands, pipe_commands);
            continue;
        }
        if (is_redirection(infos, commands[i]))
            commands[i] = save_redirection(infos, commands[i]);
        infos->input_parse = split(commands[i], " \t\n");
        if (infos->input_parse[0] != NULL)
            infos->exit_code = execute_command(infos, built_in_commands);
    }
    return 0;
}

static int process_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    free_last_command(infos->input_parse);
    if (history(infos, infos->input) == 84) {
        infos->exit_code = 1;
        return 1;
    }
    if (infos->exit_code != 1 && my_strcmp(infos->input, "history\n") != 0)
        infos->history = add_to_history(infos, infos->input);
    parse_input(infos, built_in_commands);
    return 0;
}

int mysh(int ac, char **av, char **env)
{
    size_t buff_size = 32;
    infos_t *infos = init_infos(env);
    int (*built_in_commands[NB_BUILT_IN])(infos_t *) = {
        &cd_func, &setenv_func, &unsetenv_func, NULL, &env_func, &history_func,
        &set_func
    };

    while (infos->run == 1) {
        get_cwd(infos);
        if (isatty(0) != 0)
            my_putstr(infos->line_cwd);
        if (getline(&(infos->input), &buff_size, stdin) == -1)
            break;
        process_input(infos, built_in_commands);
    }
    if (infos->run == 1 && isatty(0) != 0)
        my_putstr("exit\n");
    return infos->exit_code;
}
