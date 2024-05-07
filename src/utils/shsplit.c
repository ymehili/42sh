/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** shsplit
*/

#include "../../include/sh.h"

static int is_escape_char(shsplit_t *shsplit, int i)
{
    if (shsplit->str[i] == '\\') {
        shsplit->tokens[shsplit->token_index][shsplit->current_token_size]
            = shsplit->str[i + 1];
        shsplit->current_token_size++;
        return 1;
    }
    return 0;
}

static int is_quote_char(shsplit_t *shsplit, int i)
{
    if ((shsplit->str[i] == '"' || shsplit->str[i] == '\'') &&
        shsplit->quote_char == '\0') {
        shsplit->quote_char = shsplit->str[i];
        return 1;
    }
    return 0;
}

static int handle_same_quote_char(shsplit_t *shsplit, int i)
{
    if (shsplit->str[i] == shsplit->quote_char) {
        shsplit->quote_char = (shsplit->str[i - 1] != '\\') ? '\0' :
            shsplit->quote_char;
        return 1;
    }
    return 0;
}

static int handle_space(shsplit_t *shsplit, int i)
{
    if (is_space(shsplit->str[i]) && shsplit->quote_char == '\0') {
        shsplit->tokens[shsplit->token_index][shsplit->current_token_size]
            = '\0';
        if (!is_space(shsplit->str[i + 1])){
            shsplit->token_index++;
            shsplit->current_token_size = 0;
        }
        return 1;
    }
    return 0;
}

static void shsplit3(shsplit_t *shsplit)
{
    for (int i = 0; shsplit->str[i] != '\0'; i++) {
        if (is_escape_char(shsplit, i)){
            i++;
            continue;
        }
        if (is_quote_char(shsplit, i))
            continue;
        if (handle_same_quote_char(shsplit, i))
            continue;
        if (handle_space(shsplit, i))
            continue;
        if (shsplit->token_index < shsplit->num_tokens) {
            shsplit->tokens[shsplit->token_index][shsplit->current_token_size]
                = shsplit->str[i];
            shsplit->current_token_size++;
        }
    }
}

static int isspacesure(shsplit_t *shsplit, int i)
{
    return is_space(shsplit->str[i]) && shsplit->quote_char == '\0' &&
        !is_space(shsplit->str[i + 1]);
}

static void process_string(shsplit_t *shsplit)
{
    for (int i = 0; shsplit->str[i] != '\0'; i++) {
        if (shsplit->str[i] == '\\') {
            i++;
            continue;
        }
        if ((shsplit->str[i] == '"' || shsplit->str[i] == '\'') &&
            shsplit->quote_char == '\0') {
            shsplit->quote_char = shsplit->str[i];
            continue;
        }
        if (shsplit->str[i] == shsplit->quote_char) {
            shsplit->quote_char = (shsplit->str[i - 1] != '\\') ? '\0' :
                shsplit->quote_char;
            continue;
        }
        if (isspacesure(shsplit, i)) {
            shsplit->num_tokens++;
            continue;
        }
    }
}

void removeleading(shsplit_t *shsplit)
{
    int space_count = 0;
    char *new_str;

    while (is_space(shsplit->str[space_count]))
        space_count++;
    new_str = strdup(shsplit->str + space_count);
    free(shsplit->str);
    shsplit->str = new_str;
}

shsplit_t *initshsplit(void)
{
    shsplit_t *shsplit = my_malloc(sizeof(shsplit_t));

    shsplit->num_tokens = 0;
    shsplit->current_token_size = 0;
    shsplit->quote_char = '\0';
    return shsplit;
}

char **shsplit(const char *str)
{
    shsplit_t *shsplit = initshsplit();

    shsplit->str = strdup(str);
    removeleading(shsplit);
    shsplit2(shsplit);
    if (shsplit->num_tokens == 0) {
        shsplit->tokens[0] = strdup(str);
        shsplit->tokens[1] = NULL;
        return shsplit->tokens;
    }
    shsplit->token_index = 0;
    shsplit->current_token_size = 0;
    shsplit->quote_char = '\0';
    shsplit3(shsplit);
    if (shsplit->quote_char == '\0' && shsplit->current_token_size > 0)
        shsplit->tokens[shsplit->token_index][shsplit->current_token_size]
            = '\0';
    shsplit->tokens[shsplit->num_tokens] = NULL;
    return shsplit->tokens;
}
