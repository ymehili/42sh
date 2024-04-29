/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** split_by_parentheses
*/

#include "../../include/sh.h"

static split_t *create_split(char *str)
{
    split_t *split = my_malloc(sizeof(split_t));

    split->result = my_malloc(sizeof(char *) * (strlen(str) + 1));
    split->depth = 0;
    split->current = my_malloc(sizeof(char) * (strlen(str) + 1));
    split->current_index = 0;
    split->result_index = 0;
    split->start = 0;
    return split;
}

static void handle_open_parenthesis(split_t *split, char *str, int i)
{
    if (split->depth == 0 && i != split->start) {
        split->current[split->current_index] = '\0';
        split->result[split->result_index] = strdup(split->current);
        split->result_index++;
        split->current_index = 0;
    }
    if (split->depth != 0) {
        split->current[split->current_index] = str[i];
        split->current_index++;
    }
    split->depth++;
    split->start = i + 1;
}

static void handle_close_parenthesis(split_t *split, char *str, int i)
{
    split->depth--;
    if (split->depth != 0) {
        split->current[split->current_index] = str[i];
        split->current_index++;
    } else {
        split->current[split->current_index] = '\0';
        split->result[split->result_index] = strdup(split->current);
        split->result_index++;
        split->current_index = 0;
    }
    split->start = i + 1;
}

static void handle_character(split_t *split, char *str, int i)
{
    if (str[i] == '{')
        handle_open_parenthesis(split, str, i);
    if (str[i] == '}')
        handle_close_parenthesis(split, str, i);
    if (str[i] != '{' && str[i] != '}') {
        split->current[split->current_index] = str[i];
        split->current_index++;
    }
}

char **split_by_bracket(char *str)
{
    split_t *split = create_split(str);
    int len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        handle_character(split, str, i);
    }
    len = strlen(str);
    if (split->start != len) {
        split->current[split->current_index] = '\0';
        split->result[split->result_index] = strdup(split->current);
        split->result_index++;
    }
    split->result[split->result_index] = NULL;
    return split->result;
}
