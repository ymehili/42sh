/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** strn_replace
*/

#include "../../include/sh.h"

void remove_line_return(infos_t *infos)
{
    int len_input = my_strlen(infos->input);

    while (infos->input[len_input - 1] == '\n') {
        infos->input[len_input - 1] = '\0';
        len_input--;
    }
    infos->input = realloc(infos->input, len_input + 2);
    if (infos->input == NULL)
        return;
    infos->input[len_input] = '\n';
    infos->input[len_input + 1] = '\0';
    len_input++;
}

int strn_replace_bis(infos_t *infos, char **bang, size_t len_bang_to_space,
    size_t len_token)
{
    size_t offset;

    if (len_token > len_bang_to_space) {
        offset = *bang - infos->input;
        infos->input = realloc(infos->input, my_strlen(infos->input) -
        len_bang_to_space + len_token + 1);
        if (infos->input == NULL)
            return 1;
        *bang = infos->input + offset;
    }
    return 0;
}

void strn_replace(infos_t *infos, char *replace, char *to_replace)
{
    char *bang = strstr(infos->input, to_replace);
    char *space;
    size_t len_bang_to_space;
    size_t len_token;
    size_t len_remainder;

    if (bang != NULL) {
        space = strchr(bang, ' ');
        len_bang_to_space = space != NULL ? space - bang : my_strlen(bang);
        len_token = my_strlen(replace);
        len_remainder = strlen(bang + len_bang_to_space) + 1;
        if (strn_replace_bis(infos, &bang, len_bang_to_space, len_token) == 1)
            return;
        if (strchr(replace, '\n') == NULL) {
            memmove(bang + len_token, bang + len_bang_to_space, len_remainder);
            memcpy(bang, replace, len_token);
        }
    }
    remove_line_return(infos);
}
