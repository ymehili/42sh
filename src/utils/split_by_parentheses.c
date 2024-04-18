/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** split_by_parentheses
*/

#include "../../include/sh.h"

char **split_by_parentheses(char *str)
{
    if (strchr(str, '(') == NULL && strchr(str, ')') == NULL) {
        char **result = malloc(sizeof(char *) * 2);
        result[0] = strdup(str);
        result[1] = NULL;
        return result;
    }

    char **result = malloc(sizeof(char *) * (strlen(str) + 1));
    int depth = 0;
    char *current = malloc(sizeof(char) * (strlen(str) + 1));
    int current_index = 0;
    int result_index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            if (depth != 0) {
                current[current_index++] = str[i];
            }
            depth++;
        } else if (str[i] == ')') {
            depth--;
            if (depth != 0) {
                current[current_index++] = str[i];
            } else {
                current[current_index] = '\0';
                result[result_index++] = strdup(current);
                current_index = 0;
            }
        } else {
            current[current_index++] = str[i];
        }
    }
    result[result_index] = NULL;
    free(current);
    return result;
}