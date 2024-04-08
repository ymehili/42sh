/*
** EPITECH PROJECT, 2023
** Cpool
** File description:
** my_strdup
*/

#include "../../include/sh.h"

char *my_strdup(char *src)
{
    char *str;
    int i = 0;

    if (src == NULL)
        return NULL;
    str = my_malloc(sizeof(char) * (my_strlen(src) + 1));
    if (src != NULL) {
        for (; src[i] != '\0'; i++) {
            str[i] = src[i];
        }
    }
    str[i] = '\0';
    return str;
}
