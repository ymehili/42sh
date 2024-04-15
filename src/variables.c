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
    for (int i = 0; name[i] != '\0' && name[i] != '='; i++) {
        if (is_alpha(name[i]) == 0 && is_num(name[i]) == 0) {
            printf("set: Variable name must contain "
                "alphanumeric characters.\n");
            return 84;
        }
    }
    return 0;
}

int set_func(infos_t *infos)
{
    env_var_t *var = NULL;
    int new_var = 1;

    for (int i = 1; infos->input_parse[i] != NULL; i++) {
        if (check_var_name(infos->input_parse[i]))
            return 84;
        var = my_malloc(sizeof(env_var_t));
        var->name = parse_var(infos->input_parse[i], var, &new_var);
        if (infos->input_parse[i + 1] != NULL && var->val == NULL &&
            my_strcmp(infos->input_parse[i + 1], "=") == 0 && new_var == 0) {
            var->val = my_strdup(infos->input_parse[i + 2]);
            i += 2;
        }
        var->next = infos->var_ls;
        if (var->next)
            var->next->prev = var;
        infos->var_ls = var;
    }
    return 0;
}

env_var_t *get_var_from_ls(env_var_t *var_ls, char *var_name)
{
    env_var_t *elem = var_ls;

    if (var_name == NULL || var_name[0] == '\0')
        return NULL;
    for (; elem != NULL; elem = elem->next) {
        if (my_strncmp(elem->name, var_name, my_strlen(var_name)) == 0)
            return elem;
    }
    return NULL;
}