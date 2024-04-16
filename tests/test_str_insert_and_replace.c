/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** test_str_insert_and_replace
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(str_insert_and_replace, basic_test)
{
    char *str = "Hello";
    char *to_insert = "World";
    char *result = str_insert_and_replace(str, to_insert, 2, 2);

    cr_assert_str_eq(result, "HeWorldllo");
}

Test(str_insert_and_replace, basic_test_2)
{
    char *str = "Hello world";
    char *to_insert = "how are you";
    char *result = str_insert_and_replace(str, to_insert, 6, 11);

    cr_assert_str_eq(result, "Hello how are you");
}