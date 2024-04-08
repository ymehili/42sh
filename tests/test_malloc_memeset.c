/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_malloc_memeset
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_memset, basic_test)
{
    char buffer[10];
    int size = 10;
    char c = 'A';
    char *result = my_memset(buffer, c, size);

    cr_assert_eq(result, buffer, "my_memset() did not return the pointer to the buffer");

    for (int i = 0; i < size; i++) {
        cr_assert_eq(buffer[i], c, "my_memset() did not correctly set the buffer");
    }
}

Test(my_malloc, basic_test)
{
    int size = 10;
    char *ptr = my_malloc(size);

    cr_assert_not_null(ptr, "my_malloc() returned NULL");

    for (int i = 0; i < size; i++) {
        cr_assert_eq(ptr[i], '\0', "my_malloc() did not initialize memory to '\0'");
    }
}
