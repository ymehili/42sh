/*
** EPITECH PROJECT, 2023
** B-CPE-110-LYN-1-1-organized-lucas.leclerc
** File description:
** utils
*/

#include "../../include/sh.h"

void *my_memset(void *ptr, char c, int size)
{
    char *current = ptr;

    if (ptr == NULL)
        return NULL;
    for (int i = 0; current && i < size; i++) {
        *current = c;
        current++;
    }
    return ptr;
}

void *my_malloc(int size)
{
    void *ptr = malloc(size);

    my_memset(ptr, '\0', size);
    return ptr;
}
