/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** delete_half_circle
*/

#include "../include/sh.h"

char *delete_half_circle(char *str)
{
    char *new_str = my_malloc(sizeof(char) * (my_strlen(str) + 1));
    int i = 0;
    int j = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == ')') {
            continue;
        } else {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}
