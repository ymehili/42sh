/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_my_putnbr
*/

#include "../include/sh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void setup_my_putnbr(void)
{
    cr_redirect_stdout();
}

Test(my_putnbr, basic_test, .init = setup_my_putnbr)
{
    my_putnbr(123);
    cr_assert_stdout_eq_str("123");
}

Test(my_putnbr, negative_number, .init = setup_my_putnbr)
{
    my_putnbr(-123);
    cr_assert_stdout_eq_str("-123");
}

Test(my_putnbr, zero_number, .init = setup_my_putnbr)
{
    my_putnbr(0);
    cr_assert_stdout_eq_str("0");
}