/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-lucas.leclerc
** File description:
** linked_ls_to_str
*/

#include "../../include/sh.h"

char **old_env_to_new(infos_t *infos)
{
    char **new_env = NULL;
    env_var_t *tmp = infos->env_linked_ls;
    int nb_env = 0;

    for (; tmp; tmp = tmp->next)
        nb_env++;
    new_env = my_malloc(sizeof(char *) * (nb_env + 1));
    for (int i = 0; tmp; tmp = tmp->next) {
        new_env[i] = my_strdup(tmp->name);
        new_env[i] = my_strcat(new_env[i], "=");
        new_env[i] = my_strcat(new_env[i], tmp->val);
        new_env[i] = my_strcat(new_env[i], "\n");
        i++;
    }
    return new_env;
}
