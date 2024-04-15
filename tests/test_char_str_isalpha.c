/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_char_str_isalpha
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_str_isalpha, basic_test)
{
    char *str = "Hello";
    int result = my_str_isalpha(str);

    cr_assert_eq(result, 1, "my_str_isalpha() did not return 1 for alphabetic string");
}

Test(my_str_isalpha, non_alpha_test)
{
    char *str = "Hello123";
    int result = my_str_isalpha(str);

    cr_assert_eq(result, 0, "my_str_isalpha() did not return 0 for non-alphabetic string");
}

Test(my_str_isalpha, empty_string)
{
    char *str = "";
    int result = my_str_isalpha(str);

    cr_assert_eq(result, 1, "my_str_isalpha() did not return 1 for empty string");
}

Test(my_char_isalpha, basic_test)
{
    char ch = 'H';
    int result = my_char_isalpha(ch);

    cr_assert_eq(result, 1, "my_char_isalpha() did not return 1 for alphabetic character");
}

Test(my_char_isalpha, lower_case_test)
{
    char ch = 'h';
    int result = my_char_isalpha(ch);

    cr_assert_eq(result, 1, "my_char_isalpha() did not return 1 for upper case character");
}

Test(my_char_isalpha, non_alpha_test)
{
    char ch = '1';
    int result = my_char_isalpha(ch);

    cr_assert_eq(result, 0, "my_char_isalpha() did not return 0 for non-alphabetic character");
}

Test(my_char_isnum, basic_test)
{
    char ch = '1';
    int result = my_char_isnum(ch);

    cr_assert_eq(result, 1, "my_char_isnum() did not return 1 for numeric character");
}

Test(my_char_isnum, non_num_test)
{
    char ch = 'H';
    int result = my_char_isnum(ch);

    cr_assert_eq(result, 0, "my_char_isnum() did not return 0 for non-numeric character");
}