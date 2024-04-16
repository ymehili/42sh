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
        if (my_strcmp(elem->name, var->name) == 0) {
            free(elem->val);
            elem->val = my_strdup(var->val);
            free(var->name);
            free(var->val);
            free(var);
            return 1;
        }
    }
    return 0;
}

static void set_new_var(infos_t *infos, int i)
{
    env_var_t *var = NULL;
    int new_var = 1;

    var = my_malloc(sizeof(env_var_t));
    var->name = parse_var(infos->input_parse[i], var, &new_var);
    if (infos->input_parse[i + 1] != NULL && var->val == NULL &&
        my_strcmp(infos->input_parse[i + 1], "=") == 0 && new_var == 0) {
        var->val = my_strdup(infos->input_parse[i + 2]);
        i += 2;
    }
    if (update_var(infos, var) == 0) {
        var->next = infos->var_ls;
        if (var->next)
            var->next->prev = var;
        infos->var_ls = var;
    }
}

int set_func(infos_t *infos)
{
    if (tab_len(infos->input_parse) == 1) {
        display_env(infos->var_ls, "\t");
        return 0;
    }
    for (int i = 1; infos->input_parse[i] != NULL; i++) {
        if (check_var_name(infos->input_parse[i])) {
            infos->exit_code = 1;
            return 1;
        }
        set_new_var(infos, i);
    }
    return 0;
}
