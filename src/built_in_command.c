/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** built_in_command
*/

#include "../include/sh.h"

int cd_command(infos_t *infos, env_var_t *pwd, char *pwd_tmp)
{
    char *param = infos->input_parse[1];

    if (get_nb_params(infos->input_parse) == 1 ||
        !my_strncmp(param, "--", 3)) {
        chdir(get_env_var_linked_ls(infos->env_linked_ls, "HOME")->val);
        pwd->val = get_env_var_linked_ls(infos->env_linked_ls, "HOME")->val;
        return 1;
    }
    if (!my_strncmp(param, "/", my_strlen(param))) {
        chdir("/");
        pwd->val = my_strdup("/");
        return 1;
    }
    if (!my_strncmp(param, "-", my_strlen(param))) {
        chdir(pwd_tmp);
        pwd->val = pwd_tmp;
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

static int cd_2(infos_t *infos, char *tmp2, env_var_t *pwd)
{
    char buff[PATH_MAX];
    char *tmp = cd_wave(infos);

    if (chdir(infos->input_parse[1]) == 0)
        pwd->val = getcwd(buff, PATH_MAX);
    else {
        return cd_error(infos, tmp);
    }
    return 0;
}

int cd_func(infos_t *infos)
{
    char *tmp;
    env_var_t *pwd = get_env_var_linked_ls(infos->env_linked_ls, "PWD");
    char *pwd_tmp = infos->last_pwd;

    if (cd_params_checker(infos, infos->input_parse, pwd_tmp))
        return 1;
    tmp = infos->last_pwd;
    infos->last_pwd = pwd->val;
    if (cd_command(infos, pwd, pwd_tmp))
        return 0;
    if (cd_2(infos, tmp, pwd))
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
