/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_str_isalpha
*/

#include "../../include/sh.h"

int my_str_isalpha(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (!(str[i] >= 65 && str[i] <= 90) &&
            !(str[i] >= 97 && str[i] <= 122)) {
            return 0;
        }
        i++;
    }
    return 1;
}

int my_char_isalpha(char str)
{
    if (!(str >= 65 && str <= 90) &&
        !(str >= 97 && str <= 122)) {
        return 0;
    }
    return 1;
}

int my_char_isnum(char str)
{
    if (!(str >= '0' && str <= '9')) {
        return 0;
    }
    return 1;
}
