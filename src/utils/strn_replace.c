/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** strn_replace
*/

#include "../../include/sh.h"

int strn_replace_bis(infos_t *infos, char *bang, size_t len_bang_to_space,
    size_t len_token)
{
    if (len_token > len_bang_to_space) {
        infos->input = realloc(infos->input, my_strlen(infos->input) -
        len_bang_to_space + len_token + 1);
        if (infos->input == NULL)
            return 1;
        bang = strstr(infos->input, "!");
    }
    return 0;
}

void strn_replace(infos_t *infos, char *replace)
{
    char *bang = strstr(infos->input, "!");
    char *space;
    size_t len_bang_to_space;
    size_t len_token;
    size_t len_remainder;

    if (bang != NULL) {
        space = strchr(bang, ' ');
        len_bang_to_space = space != NULL ? space - bang : my_strlen(bang);
        len_token = my_strlen(replace);
        len_remainder = strlen(bang + len_bang_to_space) + 1;
        if (strn_replace_bis(infos, bang, len_bang_to_space, len_token) == 1)
            return;
        memmove(bang + len_token, bang + len_bang_to_space, len_remainder);
        memcpy(bang, replace, len_token);
    }
}
