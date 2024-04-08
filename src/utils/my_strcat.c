/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strcat
*/

#include "../../include/sh.h"

char *my_strcat(char *dest, char *src)
{
    int len_src = my_strlen(src);
    int len_dest = my_strlen(dest);
    char *str = my_malloc(len_dest + len_src + 1);

    for (int i = 0; i < len_dest; i++) {
        str[i] = dest[i];
    }
    for (int i = 0; i < len_src; i++) {
        str[len_dest + i] = src[i];
    }
    return str;
}
