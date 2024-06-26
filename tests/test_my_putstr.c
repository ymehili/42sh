/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** test_my_putstr
*/

#include "../include/sh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void setup_my_putstr(void)
{
    cr_redirect_stdout();
}

Test(my_putstr, basic_test, .init = setup_my_putstr)
{
    my_putstr("Hello World");
    cr_assert_stdout_eq_str("Hello World");
}
