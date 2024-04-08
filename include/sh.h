/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** sh
*/

#ifndef SH_H_
    #define SH_H_
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #define NB_BUILT_IN 5
    #include <limits.h>
    #include <signal.h>
    #include "errno.h"
    #include <fcntl.h>

typedef struct env_var_s env_var_s;
struct env_var_s {
    char *name;
    char *val;
    env_var_s *next;
    env_var_s *prev;
};

typedef struct infos_s infos_s;
struct infos_s {
    char **env;
    char *last_pwd;
    env_var_s *env_linked_ls;
    char *actual_path;
    char *input;
    char **input_parse;
    char **built_in_command_name;
    int exit_code;
    int nb_pipe;
    int run;
    char *out_file_name;
    char *in_file_name;
    int input_fd;
    int output_fd;
    int input_type;
    int output_type;
};

void *my_memset(void *ptr, char c, int size);
void *my_malloc(int size);
void my_putstr(char *str);
int my_strcmp(char *s1, char *s2);
int my_strlen(char *str);
char **old_env_to_new(infos_s *infos);
char *my_strncpy(char *dest, char *src, int n);
char **split(char *str, char *separators);
int my_strncmp(char *s1, char *s2, int n);
int my_str_isalpha(char *str);
int my_char_isnum(char str);
char *my_strcat(char *dest, char *src);
int my_char_isalpha(char str);
char *my_strdup(char *src);
char **split_first(char *str, char *separators);
int get_nb_params(char **params);
char *split_to_str(char **split, int at_end);

int mysh(char **env);
int return_error(char *name, char *str, int code);
char *get_env_var(char **env, char *var_name);
int cd_func(infos_s *infos);
int setenv_func(infos_s *infos);
int unsetenv_func(infos_s *infos);
env_var_s *env_to_linked_ls(char **env);
env_var_s *get_env_var_linked_ls(env_var_s *env, char *var_name);
void display_env(env_var_s *env_ls);
int env_func(infos_s *infos);
int unsetenv_error_checker(char **params);
int setenv_error_checker(char **params);
int cd_error(char *str);
int cd_params_checker(char **params, char *last_pwd);
int exec_built_in(infos_s *infos, int built_in_nb,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_s *));
int execute_command(infos_s *infos,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_s *));
int handle_pipe(infos_s *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_s *), char **input);
int status_code(int status);
int is_built_in_command(infos_s *infos, char *command);
int exec_with_path(infos_s *infos);
char *save_redirection(infos_s *infos, char *input);
int is_redirection(infos_s *infos, char *str);
void handle_redirection(infos_s *infos);

#endif /* SH_H_ */
