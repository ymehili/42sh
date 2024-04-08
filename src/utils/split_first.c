/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** split
*/

#include "../../include/sh.h"

static int is_separator(char letter, char *separators)
{
    for (int i = 0; separators[i] != '\0'; i++) {
        if (letter == separators[i])
            return 1;
    }
    return 0;
}

static void save_words_in_ls(char **ls, char *str, char *separators)
{
    int nb = 0;
    int i = 0;

    for (; str[i] != '\0' && nb == 0; i++) {
        if (is_separator(str[i], separators)) {
            ls[0] = my_malloc(sizeof(char) * (i + 1));
            my_strncpy(ls[0], str, i);
            nb++;
        }
    }
    ls[1] = my_strdup(&str[i]);
}

static int split_first_2(char *str, char *separators, int i)
{
    int nb_sep = 0;

    for (int j = 0; separators[j] != '\0'; j++) {
        if (str[i] == separators[j])
            nb_sep += 1;
    }
    return nb_sep;
}

char **split_first(char *str, char *separators)
{
    char **words_ls = my_malloc(sizeof(char *) * 3);
    int nb_sep = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        nb_sep += split_first_2(str, separators, i);
    }
    if (nb_sep == 0) {
        words_ls[0] = str;
        return words_ls;
    }
    save_words_in_ls(words_ls, str, separators);
    return words_ls;
}
