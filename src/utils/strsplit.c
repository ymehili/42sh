/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** string_str_to_word_array
*/

#include "../include/sh.h"

char **strsplit(const char *input, const char *delimiter)
{
    int i = 0;
    char **result = my_malloc(strlen(input) * sizeof(char *));
    char *string = strdup(input);
    char *start = string;
    char *end = strstr(start, delimiter);

    while (end != NULL) {
        *end = '\0';
        result[i] = strdup(start);
        start = end + strlen(delimiter);
        i++;
        end = strstr(start, delimiter);
    }
    result[i] = strdup(start);
    free(string);
    return result;
}
