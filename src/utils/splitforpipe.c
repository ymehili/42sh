/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell1-lucas.leclerc
** File description:
** split
*/

#include "../../include/sh.h"

static int is_separator(char letter, char next_letter, char *separators)
{
    for (int i = 0; separators[i] != '\0'; i++) {
        if (letter == separators[i]) {
            if (letter == '|' && next_letter == '|') {
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

static int words_counter(char *str, char *separators)
{
    int in_word = 0;
    int nb_words = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (in_word == 0 && is_separator(str[i], str[i + 1], separators) != 1)
            in_word = 1;
        if (in_word == 1 && is_separator(str[i], str[i + 1], separators) &&
            is_separator(str[i + 1], str[i + 2], separators)) {
            nb_words++;
            in_word = 0;
        }
    }
    if (in_word)
        nb_words++;
    return nb_words;
}

static void save_words_in_ls_2(int *in_word, int *start, int i)
{
    *in_word = 1;
    *start = i;
}

static void save_words_in_ls(char **ls, char *str, char *separators)
{
    int in_word = 0;
    int start;
    int nb = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (in_word == 0 && is_separator(str[i], str[i + 1], separators) != 1)
            save_words_in_ls_2(&in_word, &start, i);
        if (in_word == 1 && is_separator(str[i], str[i + 1], separators) &&
            is_separator(str[i + 1], str[i + 2], separators)) {
            ls[nb] = my_malloc(sizeof(char) * (i - start + 1));
            my_strncpy(ls[nb], &str[start], i - start);
            nb++;
            in_word = 0;
        }
    }
    if (in_word == 1) {
        ls[nb] = my_malloc(sizeof(char) * (i - start + 1));
        my_strncpy(ls[nb], &str[start], i - start);
    }
}

char **splitforpipe(char *str, char *separators)
{
    int nb_word = words_counter(str, separators);
    char **words_ls = my_malloc(sizeof(char *) * (nb_word + 1));

    save_words_in_ls(words_ls, str, separators);
    return words_ls;
}
