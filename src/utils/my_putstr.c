/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** my_putstr
*/

#include "../../include/sh.h"

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    for (; str[i] != '\0'; i++);
    return i;
}

void my_putstr(char *str)
{
    int size = my_strlen(str);

    write(1, str, size);
}
