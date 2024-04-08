/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** error_handler
*/

#include "../include/sh.h"

int cd_params_checker(char **params, char *last_pwd)
{
    if (get_nb_params(params) != 1 && get_nb_params(params) != 2)
        return return_error(params[0], ": Too many arguments.\n", 1);
    if (get_nb_params(params) != 1 && my_strncmp(params[1], "-", 1) == 0 &&
        last_pwd == NULL)
        return return_error("", ": No such file or directory.\n", 1);
    return 0;
}

int cd_error(char *str)
{
    switch (errno) {
        case ENOENT:
            return return_error(str, ": No such file or directory.\n", 1);
        case ENOTDIR:
            return return_error(str, ": Not a directory.\n", 1);
        case EACCES:
            return return_error(str, ": Permission denied.\n", 1);
    }
    return 1;
}

int setenv_error_checker(char **params)
{
    if (get_nb_params(params) > 3) {
        my_putstr(params[0]);
        my_putstr(": Too many arguments.\n");
        return 1;
    }
    if (get_nb_params(params) == 1)
        return 0;
    if (my_char_isalpha(params[1][0]) == 0)
        return return_error(params[0],
            ": Variable name must begin with a letter.\n", 1);
    for (int i = 0; params[1][i] != '\0'; i++) {
        if (my_char_isalpha(params[1][i]) != 1 &&
            my_char_isnum(params[1][i]) != 1)
            return return_error(params[0],
            ": Variable name must contain alphanumeric characters.\n", 1);
    }
    return 0;
}

int unsetenv_error_checker(char **params)
{
    if (get_nb_params(params) == 1) {
        my_putstr(params[0]);
        my_putstr(": Too few arguments.\n");
        return 1;
    }
    return 0;
}
