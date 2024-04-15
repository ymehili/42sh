/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_my_strn_is_num
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_strn_is_num, basic_test)
{
    char str[] = "123";

    int res = my_strn_is_num(str, 2);

    cr_assert_eq(res, 1);
}

Test(my_strn_is_num, non_num_test)
{
    char str[] = "123Hello";

    int res = my_strn_is_num(str, 2);

    cr_assert_eq(res, 0);
}

Test(my_strn_is_num, empty_string)
{
    char str[] = "";

    int res = my_strn_is_num(str, 0);

    cr_assert_eq(res, 0);
}

Test(my_strn_is_num, string_with_newline)
{
    char str[] = "123\n";

    int res = my_strn_is_num(str, 3);

    cr_assert_eq(res, 1);
}