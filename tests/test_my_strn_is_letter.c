/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_my_strn_is_letter
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_strn_is_letter, basic_test)
{
    char str[] = "Hello";

    int res = my_strn_is_letter(str, 4);

    cr_assert_eq(res, 1);
}

Test(my_strn_is_letter, non_alpha_test)
{
    char str[] = "Hello123";

    int res = my_strn_is_letter(str, 6);

    cr_assert_eq(res, 0);
}

Test(my_strn_is_letter, empty_string)
{
    char str[] = "";

    int res = my_strn_is_letter(str, 0);

    cr_assert_eq(res, 0);
}

Test(my_strn_is_letter, string_with_newline)
{
    char str[] = "Hello\n";

    int res = my_strn_is_letter(str, 5);

    cr_assert_eq(res, 1);
}
