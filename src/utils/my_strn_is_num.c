/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** my_strn_is_num
*/

#include "../../include/sh.h"

int my_strn_is_num(char *str, int n)
{
    if (str[n] == '\0')
        return 0;
    for (int i = n; str[i] != '\0'; i++) {
        if (str[i] == '\n')
            return 1;
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
