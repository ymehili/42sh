/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** built_in_command
*/

#include "../include/sh.h"

int cd_command(infos_t *infos, char *param, env_var_t *pwd, env_var_t *old_pwd)
{
    if (get_nb_params(infos->input_parse) == 1 ||
        !my_strncmp(param, "--", 3)) {
        chdir(get_env_var_linked_ls(infos->env_linked_ls, "HOME")->val);
        old_pwd->val = pwd->val;
        pwd->val = get_env_var_linked_ls(infos->env_linked_ls, "HOME")->val;
        return 1;
    }
    if (!my_strncmp(param, "/", my_strlen(param))) {
        chdir("/");
        old_pwd->val = pwd->val;
        pwd->val = my_strdup("/");
        return 1;
    }
    if (!my_strncmp(param, "-", my_strlen(param))) {
        chdir(old_pwd->val);
        pwd->val = old_pwd->val;
        return 1;
    }
    return 0;
}

static char *cd_wave(infos_t *infos)
{
    char *tmp = infos->input_parse[1];

    if (infos->input_parse[1][0] == '~')
        infos->input_parse[1] = my_strcat(
            get_env_var_linked_ls(infos->env_linked_ls, "HOME")->val,
            &(infos->input_parse[1][1]));
    return tmp;
}

static int cd_2(infos_t *infos)
{
    char buff[PATH_MAX];
    char *tmp = cd_wave(infos);
    env_var_t *pwd = get_env_var_linked_ls(infos->env_linked_ls, "PWD");
    env_var_t *old_pwd = get_env_var_linked_ls(infos->env_linked_ls, "OLDPWD");

    if (chdir(infos->input_parse[1]) == 0) {
        old_pwd->val = pwd->val;
        pwd->val = getcwd(buff, PATH_MAX);
    } else {
        return cd_error(infos, tmp);
    }
    return 0;
}

int cd_func(infos_t *infos)
{
    char *param = infos->input_parse[1];
    env_var_t *pwd = get_env_var_linked_ls(infos->env_linked_ls, "PWD");
    env_var_t *old_pwd = get_env_var_linked_ls(infos->env_linked_ls, "OLDPWD");

    if (cd_params_checker(infos, infos->input_parse, old_pwd->val))
        return 1;
    if (cd_command(infos, param, pwd, old_pwd))
        return 0;
    if (cd_2(infos))
        return 1;
    return 0;
}

static void new_env(infos_t *infos, env_var_t *new)
{
    new->name = my_strdup(infos->input_parse[1]);
    new->val = get_nb_params(infos->input_parse) == 2 ?
        my_strdup("") : my_strdup(infos->input_parse[2]);
    new->next = infos->env_linked_ls;
    if (infos->env_linked_ls != NULL)
        infos->env_linked_ls->prev = new;
    new->prev = NULL;
    infos->env_linked_ls = new;
}

int setenv_func(infos_t *infos)
{
    env_var_t *elem = get_env_var_linked_ls(infos->env_linked_ls,
        infos->input_parse[1]);
    env_var_t *new;

    if (setenv_error_checker(infos, infos->input_parse))
        return 1;
    if (infos->input_parse[1] == NULL) {
        display_env(infos->env_linked_ls, "=");
        return 0;
    }
    if (elem != NULL)
        elem->val = get_nb_params(infos->input_parse) == 2 ?
            my_strdup("") : my_strdup(infos->input_parse[2]);
    else {
        new = (env_var_t *)my_malloc(sizeof(env_var_t));
        new_env(infos, new);
    }
    return 0;
}

int unsetenv_func(infos_t *infos)
{
    env_var_t *elem;

    if (unsetenv_error_checker(infos->input_parse))
        return 1;
    for (int i = 1; infos->input_parse[i] != NULL; i++) {
        elem = get_env_var_linked_ls(infos->env_linked_ls,
            infos->input_parse[i]);
        if (elem == NULL)
            continue;
        if (elem->next != NULL)
            elem->next->prev = elem->prev;
        if (elem->prev != NULL)
            elem->prev->next = elem->next;
        else
            infos->env_linked_ls = elem->next;
        free(elem->val);
        free(elem->name);
        free(elem);
    }
    return 0;
}

int env_func(infos_t *infos)
{
    if (get_nb_params(infos->input_parse) > 1) {
        my_putstr(infos->input_parse[0]);
        my_putstr(": Too many arguments.\n");
        return 1;
    }
    display_env(infos->env_linked_ls, "=");
    return 0;
}
