/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_strncmp
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_strncmp, equal_strings)
{
    char *s1 = "Hello";
    char *s2 = "Hello";
    int n = 5; 

    int result = my_strncmp(s1, s2, n);
    cr_assert_eq(result, 0, "my_strncmp() did not return 0 for equal strings");
}

Test(my_strncmp, different_strings)
{
    char *s1 = "Hello";
    char *s2 = "World";
    int n = 5;

    int result = my_strncmp(s1, s2, n);
    cr_assert_neq(result, 0, "my_strncmp() did not return a non-zero value for different strings");
}

Test(my_strncmp, partial_comparison)
{
    char *s1 = "Hello";
    char *s2 = "Heaven";
    int n = 2;

    int result = my_strncmp(s1, s2, n);
    cr_assert_eq(result, 0, "my_strncmp() did not return 0 for partial comparison");
}