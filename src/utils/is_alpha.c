/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** is_alpha
*/

#include "../../include/sh.h"

int is_alpha(char str)
{
    if ((str < 'A' || str > 'Z') && (str < 'a' || str > 'z'))
        return 0;
    return 1;
}

int is_num(char str)
{
    if (str < '0' || str > '9')
        return 0;
    return 1;
}
