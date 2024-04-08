/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** test_strcpy
*/

#include "../include/sh.h"
#include <criterion/criterion.h>

Test(my_strncpy, basic_test)
{
    char src[] = "Hello World!";
    char dest[20]; // Assurez-vous que dest a assez d'espace pour accueillir la copie
    int n = 5; // Copier les 5 premiers caractères

    char *result = my_strncpy(dest, src, n);

    cr_assert_str_eq(dest, "Hello"); // Vérifie que la copie a été faite correctement
    cr_assert_eq(result, dest, "my_strncpy() did not return dest");

    // N'oubliez pas de tester le cas où src est plus court que n et de vérifier le contenu de dest
}

Test(my_strncpy, src_shorter_than_n)
{
    char src[] = "Hi";
    char dest[20];
    int n = 5;

    char *result = my_strncpy(dest, src, n);

    cr_assert_str_eq(dest, "Hi");
    cr_assert_eq(result, dest, "my_strncpy() did not return dest");
}

Test(my_strncpy, src_longer_than_n)
{
    char src[] = "This is a long string";
    char dest[20];
    int n = 5;

    char *result = my_strncpy(dest, src, n);

    cr_assert_str_eq(dest, "This ");
    cr_assert_eq(result, dest, "my_strncpy() did not return dest");
}
