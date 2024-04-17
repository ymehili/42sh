/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** str_insert_and_replace
*/

#include "../../include/sh.h"

char *str_insert_and_replace(char *str, char *insert, int start, int end)
{
    char *new_str = my_malloc(sizeof(char) *
        (my_strlen(str) + my_strlen(insert) + 1));
    int i = 0;
    int j = 0;

    if (str == NULL || insert == NULL)
        return NULL;
    for (; i < start; i++)
        new_str[i] = str[i];
    for (; insert[j] != '\0'; j++) {
        new_str[i] = insert[j];
        i++;
    }
    for (; str[end] != '\0'; end++) {
        new_str[i] = str[end];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}
