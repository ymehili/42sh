/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** split_to_str
*/

#include "../../include/sh.h"

char *split_to_str(char **split, char separator, int at_end)
{
    int len = at_end ? 1 : 0;
    char *str;

    for (int i = 0; split[i] != NULL; i++)
        len += my_strlen(split[i]) + 1;
    str = my_malloc(sizeof(char) * len);
    for (int i = 0; split[i] != NULL; i++) {
        str = my_strcat(str, split[i]);
        if (split[i + 1] != NULL || at_end)
            str = my_strcat(str, "/");
    }
    return str;
}
