/*
** EPITECH PROJECT, 2024
** B-PSU-200-LYN-2-1-minishell2-lucas.leclerc
** File description:
** redirection
*/

#include "../include/sh.h"

static int is_red_2(infos_s *infos, char *str, int *i)
{
    if (str[*i] == '>') {
        if (str[*i + 1] == '>') {
            infos->output_type = 2;
            *i += 1;
            return 2;
        }
        infos->output_type = 1;
        return 1;
    }
    if (str[*i] == '<') {
        if (str[*i + 1] == '<') {
            infos->input_type = 2;
            *i += 1;
            return 4;
        }
        infos->input_type = 1;
        return 3;
    }
    return 0;
}

int is_redirection(infos_s *infos, char *str)
{
    infos->input_type = 0;
    infos->output_type = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        is_red_2(infos, str, &i);
    }
    if (infos->input_type != 0 || infos->output_type != 0)
        return 1;
    return 0;
}

char *save_redirection(infos_s *infos, char *input)
{
    char *command = input;

    infos->in_file_name = NULL;
    infos->out_file_name = NULL;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '<') {
            input[i] = '\0';
            infos->in_file_name = split(&input[i + 1], " \t\n<")[0];
            input = input[i + 1] == '<' ? &input[i + 2] : &input[i + 1];
            i = 0;
        }
        if (input[i] == '>') {
            input[i] = '\0';
            infos->out_file_name = split(&input[i + 1], " \t\n>")[0];
        }
    }
    return command;
}

void check_redirection(infos_s *infos)
{
    if (infos->input_type != 0 && infos->in_file_name == NULL) {
        return_error(NULL, "Missing name for redirect.\n", 1);
        exit(1);
    }
    if (infos->output_type != 0 && infos->out_file_name == NULL) {
        return_error(NULL, "Missing name for redirect.\n", 1);
        exit(1);
    }
    if (infos->input_type != 0 && infos->output_type != 0 &&
        my_strcmp(infos->in_file_name, infos->out_file_name) == 0) {
        return_error(infos->input_parse[0],
            ": (standard input): input file is also output\n", 1);
        exit(1);
    }
}

void handle_redirection(infos_s *infos)
{
    check_redirection(infos);
    if (infos->input_type != 0) {
        infos->input_fd = open(infos->in_file_name, O_RDONLY);
        if (infos->input_fd == -1) {
            return_error(infos->in_file_name,
                ": No such file or directory.\n", 1);
            exit(1);
        }
        dup2(infos->input_fd, STDIN_FILENO);
    }
    if (infos->output_type != 0) {
        if (infos->output_type == 2)
            infos->output_fd = open(infos->out_file_name,
                O_CREAT | O_WRONLY | O_APPEND, 0666);
        else
            infos->output_fd = open(infos->out_file_name,
                O_CREAT | O_WRONLY | O_TRUNC, 0666);
        dup2(infos->output_fd, STDOUT_FILENO);
    }
}
