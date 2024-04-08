/*
** EPITECH PROJECT, 2023
** B-CPE-100-LYN-1-1-cpoolday06-lucas.leclerc
** File description:
** my_strmp
*/

#include "../../include/sh.h"

int my_strncmp(char *s1, char *s2, int n)
{
    while (n && *s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) {
        return 0;
    } else {
        return (*s1 - *s2);
    }
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return 0;
}
