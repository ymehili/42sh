/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_my_getnbr
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_getnbr, basic_test)
{
    char str[] = "123";

    int res = my_getnbr(str);

    cr_assert_eq(res, 123);
}

Test(my_getnbr, negativ_number)
{
    char str[] = "-123";

    int res = my_getnbr(str);

    cr_assert_eq(res, -123);
}