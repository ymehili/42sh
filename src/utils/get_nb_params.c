/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** get_nb_params
*/

#include "../../include/sh.h"

int get_nb_params(char **params)
{
    int i = 0;

    for (; params[i] != NULL; i++);
    return i;
}
