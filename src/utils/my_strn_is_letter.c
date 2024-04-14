/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** my_strn_is_letter
*/

#include "../../include/sh.h"

int my_strn_is_letter(char *str, int n)
{
    if (str[n] == '\0')
        return 0;
    for (int i = n; str[i] != '\0'; i++) {
        if (str[i] == '\n')
            return 1;
        if ((str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z'))
            return 0;
    }
    return 1;
}
