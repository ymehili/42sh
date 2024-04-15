/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** my_putnbr
*/

#include "../../include/sh.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar(nb % 10 + '0');
}
