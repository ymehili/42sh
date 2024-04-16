/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** get_env
*/

#include "../include/sh.h"

char *get_env_var(char **env, char *var_name)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], var_name, my_strlen(var_name)) == 0)
            return &(env[i][my_strlen(var_name) + 1]);
    }
    return NULL;
}

void display_env(env_var_t *env_ls, char *sep)
{
    env_var_t *elem = env_ls;

    if (elem == NULL)
        return;
    for (; elem->next != NULL; elem = elem->next);
    for (; elem != NULL; elem = elem->prev) {
        my_putstr(elem->name);
        my_putstr(sep);
        my_putstr(elem->val);
        my_putstr("\n");
    }
}

env_var_t *get_env_var_linked_ls(env_var_t *env, char *var_name)
{
    env_var_t *elem = env;

    if (var_name == NULL || var_name[0] == '\0')
        return NULL;
    for (; elem != NULL; elem = elem->next) {
        if (my_strncmp(elem->name, var_name, my_strlen(var_name)) == 0)
            return elem;
    }
    return NULL;
}

env_var_t *env_to_linked_ls(char **env)
{
    char **env_var;
    env_var_t *new;
    env_var_t *head = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        env_var = split_first(env[i], "=");
        new = my_malloc(sizeof(env_var_t));
        new->name = env_var[0];
        new->val = env_var[1];
        new->prev = NULL;
        if (head != NULL)
            head->prev = new;
        new->next = head;
        head = new;
    }
    return head;
}
