/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** mysh
*/
#include "../include/sh.h"

int return_error(infos_t *infos, char *name, char *str, int code)
{
    if (infos->is_a_job != 1) {
        write(2, name, my_strlen(name));
        write(2, str, my_strlen(str));
        return code;
    }
    return 0;
}

static void init_builtins(infos_t *infos)
{
    infos->built_in_command_name = my_malloc(
        sizeof(char *) * (NB_BUILT_IN + 1));
    infos->built_in_command_name[0] = my_strdup("cd");
    infos->built_in_command_name[1] = my_strdup("setenv");
    infos->built_in_command_name[2] = my_strdup("unsetenv");
    infos->built_in_command_name[3] = my_strdup("exit");
    infos->built_in_command_name[4] = my_strdup("env");
    infos->built_in_command_name[5] = my_strdup("history");
    infos->built_in_command_name[6] = my_strdup("set");
    infos->built_in_command_name[7] = my_strdup("alias");
    infos->built_in_command_name[8] = my_strdup("unalias");
    infos->built_in_command_name[9] = my_strdup("fg");
    return;
}

infos_t *init_infos(char **env)
{
    infos_t *infos = my_malloc(sizeof(infos_t));

    infos->input = my_malloc(sizeof(char) * 32);
    infos->env = env;
    infos->history = NULL;
    infos->env_linked_ls = env_to_linked_ls(env);
    init_builtins(infos);
    infos->exit_code = 0;
    infos->input_fd = STDIN_FILENO;
    infos->run = 1;
    infos->is_a_job = 0;
    save_last_command_in_var(infos, NULL);
    return infos;
}

static int check_pipe_2(char **pipe_commands)
{
    char *tmp;
    int nb = 0;

    for (int i = 0; pipe_commands[i] != NULL; i++) {
        tmp = shsplit(pipe_commands[i])[0];
        if (tmp == NULL || tmp[0] == '\0')
            break;
        nb++;
    }
    return nb;
}

int check_pipe(infos_t *infos, char *input)
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

int process_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *))
{
    char *tmp;

    if (history(infos, infos->input) == 84) {
        infos->exit_code = 1;
        return 1;
    }
    if (infos->exit_code != 1 && my_strcmp(infos->input, "history\n") != 0)
        infos->history = add_to_history(infos, my_strdup(infos->input));
    find_alias(infos, infos->input);
    tmp = my_strdup(infos->input);
    if (change_variable(infos))
        return 1;
    save_last_command_in_var(infos, tmp);
    parse_input(infos, built_in_commands);
    return 0;
}

int mysh(int ac, char **av, char **env)
{
    size_t buff_size = 32;
    infos_t *infos = init_infos(env);
    int (*built_in_commands[NB_BUILT_IN])(infos_t *) = {
        &cd_func, &setenv_func, &unsetenv_func, NULL, &env_func, &history_func,
        &set_func, &alias_func, &unalias_func, &fg_func
    };

    file_rc(infos, built_in_commands);
    while (infos->run == 1) {
        get_cwd(infos);
        if (isatty(0) != 0)
            my_putstr(infos->line_cwd);
        if (getline(&(infos->input), &buff_size, stdin) == -1)
            break;
        process_input(infos, built_in_commands);
    }
    free_all(infos);
    if (infos->run == 1 && isatty(0) != 0)
        my_putstr("exit\n");
    return infos->exit_code;
}
