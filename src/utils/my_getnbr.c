/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** my_getnbr
*/

#include "../../include/sh.h"

int my_getnbr(char *str)
{
    int i = 0;
    int nb = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            break;
    }
    for (int j = 0; str[i + j] != '\0' &&
        (str[i + j] >= '0' && str[i + j] <= '9'); j++) {
        nb = nb * 10;
        nb += str[i + j] - '0';
    }
    if (i > 0 && str[i - 1] == '-')
        nb = nb * -1;
    return nb;
}
