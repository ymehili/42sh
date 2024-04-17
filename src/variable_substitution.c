/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** variable_substitution
*/

#include "../include/sh.h"

int change_variable_bis(infos_t *infos, int i)
{
    int j = i + 1;
    char *var_name = NULL;
    env_var_t *var = NULL;

    for (; infos->input[j] != '\0' && infos->input[j] != ' ' &&
        infos->input[j] != '\t' && infos->input[j] != '\n' &&
        infos->input[j] != '$'; j++);
    if (i == j - 1)
        return j;
    var_name = my_malloc(sizeof(char) * (j - i));
    var_name = my_strncpy(var_name, &infos->input[i + 1], j - i - 1);
    var = get_var(infos, var_name);
    if (var == NULL) {
        printf("%s: Undefined variable.\n", var_name);
        infos->exit_code = 1;
        return -1;
    }
    infos->input = str_insert_and_replace(infos->input,
        var->val, i, j);
    return i + my_strlen(var->val) - 1;
}

static int status_variable(infos_t *infos, int i)
{
    char *status = my_malloc(sizeof(char) * 5);

    sprintf(status, "%d", infos->exit_code);
    if (infos->input[i + 1] == '?') {
        infos->input = str_insert_and_replace(infos->input,
            status, i, i + 2);
        i += my_strlen(status) - 1;
        free(status);
        return i;
    }
    free(status);
    return i;
}

static int pid_variable(infos_t *infos, int i)
{
    char *pid = my_malloc(sizeof(char) * 5);

    sprintf(pid, "%d", getpid());
    if (infos->input[i + 1] == '$') {
        infos->input = str_insert_and_replace(infos->input,
            pid, i, i + 2);
        i += my_strlen(pid) - 1;
        free(pid);
        return i;
    }
    free(pid);
    return i;
}

static int input_variable(infos_t *infos, int i)
{
    size_t size = 0;
    char *line = NULL;

    if (getline(&line, &size, stdin) == -1) {
        free(line);
        return -1;
    }
    infos->input = str_insert_and_replace(infos->input,
        line, i, i + 2);
    i += my_strlen(line) - 1;
    free(line);
    return i;
}

int change_variable_define(infos_t *infos, int i)
{
    int tmp = status_variable(infos, i);
    char *last;

    if (tmp != i)
        return tmp;
    tmp = pid_variable(infos, i);
    if (tmp != i)
        return tmp;
    if (infos->input[i + 1] == '_') {
        last = get_var(infos, "_")->val;
        infos->input = str_insert_and_replace(infos->input,
            last, i, i + 2);
        return i + my_strlen(last) - 1;
    }
    if (infos->input[i + 1] == '<') {
        return input_variable(infos, i);
    }
    return i;
}

int change_variable(infos_t *infos)
{
    int tmp;

    for (int i = 0; infos->input[i] != '\0'; i++) {
        tmp = i;
        if (infos->input[i] == '$')
            i = change_variable_define(infos, i);
        if (tmp == i && infos->input[i] == '$')
            i = change_variable_bis(infos, i);
        if (i < 0)
            return 84;
    }
    return 0;
}
