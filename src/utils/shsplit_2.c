/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-42sh-enzo.gaggiotti
** File description:
** shsplit_2
*/

#include "../include/sh.h"

void shsplit2(shsplit_t *shsplit)
{
    process_string(shsplit);
    if (shsplit->quote_char == '\0' && shsplit->current_token_size > 0)
        shsplit->num_tokens++;
    shsplit->tokens = my_malloc(sizeof(char *) * (shsplit->num_tokens + 10));
    for (int i = 0; i < shsplit->num_tokens; i++) {
        shsplit->tokens[i] = my_malloc(100);
    }
}
