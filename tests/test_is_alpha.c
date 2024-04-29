/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_is_alpha
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(is_alpha, should_return_1)
{
    int res = is_alpha('a');
    cr_assert_eq(res, 1);
}

Test(is_alpha, should_return_0)
{
    int res = is_alpha('1');
    cr_assert_eq(res, 0);
}

Test(is_num, should_return_1)
{
    int res = is_num('1');
    cr_assert_eq(res, 1);
}

Test(is_num, should_return_0)
{
    int res = is_num('a');
    cr_assert_eq(res, 0);
}