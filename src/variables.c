/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** variables
*/

#include "../include/sh.h"

static char *parse_var(char *str2, env_var_t *var, int *new_var)
{
    int i = 0;
    int found = 0;
    char *str = my_strdup(str2);

    for (i = 0; str[i] != '\0' && str[i] != '='; i++);
    if (str[i] == '=') {
        str[i] = '\0';
        found = 1;
    }
    if (found && my_strlen(&str[i + 1]))
        var->val = my_strdup(&str[i + 1]);
    if (found == 0)
        *new_var = 0;
    return str;
}

static int check_var_name(char *name)
{
    if (name == NULL || is_alpha(name[0]) == 0) {
        printf("set: Variable name must begin with a letter.\n");
        return 84;
    }
    return 0;
}

int update_var(infos_t *infos, env_var_t *var)
{
    env_var_t *elem = infos->var_ls;

    for (; elem != NULL; elem = elem->next) {
        if (my_strcmp(elem->name, var->name) == 0 && elem->read_only == 0) {
            free(elem->val);
            elem->val = my_strdup(var->val);
            free(var->name);
            free(var->val);
            free(var);
            return 1;
        }
        if (my_strcmp(elem->name, var->name) == 0 && elem->read_only == 1) {
            printf("set: $%s is read-only.\n", var->name);
            free(var->name);
            free(var->val);
            free(var);
            return 1;
        }
    }
    return 0;
}

static int set_new_var(infos_t *infos, int i, int read_only)
{
    env_var_t *var = NULL;
    int new_var = 1;
    int output = 0;

    var = my_malloc(sizeof(env_var_t));
    var->name = parse_var(infos->input_parse[i], var, &new_var);
    if (infos->input_parse[i + 1] != NULL && var->val == NULL &&
        my_strcmp(infos->input_parse[i + 1], "=") == 0 && new_var == 0) {
        var->val = my_strdup(infos->input_parse[i + 2]);
        i += 2;
    }
    var->read_only = read_only;
    output = update_var(infos, var);
    if (output == 0) {
        var->next = infos->var_ls;
        if (var->next)
            var->next->prev = var;
        infos->var_ls = var;
    }
    return output;
}

int static display_env_bis(infos_t *infos)
{
    if (tab_len(infos->input_parse) == 1 ||
        (tab_len(infos->input_parse) == 2 &&
        my_strcmp(infos->input_parse[1], "-r") == 0)) {
        display_env(infos->var_ls, "\t");
        return 1;
    }
    return 0;
}

int set_func(infos_t *infos)
{
    int read_only = 0;

    if (display_env_bis(infos))
        return 0;
    if (my_strcmp(infos->input_parse[1], "-r") == 0)
        read_only = 1;
    for (int i = 1 + read_only; infos->input_parse[i] != NULL; i++) {
        if (check_var_name(infos->input_parse[i])) {
            infos->exit_code = 1;
            return 1;
        }
        if (set_new_var(infos, i, read_only) == -1) {
            infos->exit_code = 1;
            return 1;
        }
    }
    return 0;
}

env_var_t *get_var(infos_t *infos, char *var_name)
{
    env_var_t *elem = infos->var_ls;

    for (; elem != NULL; elem = elem->next) {
        if (my_strcmp(elem->name, var_name) == 0)
            return elem;
    }
    return NULL;
}

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

int change_variable(infos_t *infos)
{
    for (int i = 0; infos->input[i] != '\0'; i++) {
        if (infos->input[i] == '$')
            i = change_variable_bis(infos, i);
        if (i < 0)
            return 84;
    }
    return 0;
}
