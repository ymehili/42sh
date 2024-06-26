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
    #define NB_BUILT_IN 11
    #define BUFFER_SIZE 1024
    #define MAX_ALIAS 100
    #include <limits.h>
    #include <signal.h>
    #include "errno.h"
    #include <fcntl.h>
    #include <time.h>
    #include <string.h>
    #include <stdbool.h>

typedef struct env_var_s env_var_t;
struct env_var_s {
    char *name;
    char *val;
    int read_only;
    env_var_t *next;
    env_var_t *prev;
};

typedef struct history_s history_t;
struct history_s {
    int id;
    char *time;
    char *command;
    history_t *next;
    history_t *prev;
};

typedef struct alias_set_s alias_set_t;
struct alias_set_s {
    char *alias[MAX_ALIAS];
    int count;
};

typedef struct alias_s alias_t;

struct alias_s {
    char *alias;
    char *command;
    alias_t *next;
    alias_t *prev;
};

typedef struct job_s job_t;

struct job_s {
    pid_t pid;
    int pos;
    int finished;
    char *command;
    job_t *prev;
    job_t *next;
};

typedef struct infos_s infos_t;
struct infos_s {
    char **env;
    char *last_pwd;
    char *line_cwd;
    env_var_t *env_linked_ls;
    env_var_t *var_ls;
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
    history_t *history;
    alias_t *alias;
    alias_set_t *alias_set;
    int is_backtick;
    char *backtick_output;
    char *input_tmp_backtick;
    job_t *jobs;
    job_t *first_job;
    int is_a_job;
};

typedef struct split_s {
    char **result;
    int depth;
    char *current;
    int current_index;
    int result_index;
    int start;
} split_t;



void *my_memset(void *ptr, char c, int size);
void *my_malloc(int size);
void my_putstr(char *str);
int my_strcmp(char *s1, char *s2);
int my_strlen(char *str);
char **old_env_to_new(infos_t *infos);
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
char **split_by_bracket(char *str);
char *split_to_str(char **split, int at_end);
char **strsplit(const char *str, const char *delim);
int free_all(infos_t *infos);

int mysh(int ac, char **av, char **env);
int return_error(infos_t *infos, char *name, char *str, int code);
char *get_env_var(char **env, char *var_name);
int cd_func(infos_t *infos);
int setenv_func(infos_t *infos);
int unsetenv_func(infos_t *infos);
env_var_t *env_to_linked_ls(char **env);
env_var_t *get_env_var_linked_ls(env_var_t *env, char *var_name);
void display_env(env_var_t *env_ls, char *sep);
int env_func(infos_t *infos);
int unsetenv_error_checker(char **params);
int setenv_error_checker(infos_t *infos, char **params);
int cd_error(infos_t *infos, char *str);
int cd_params_checker(infos_t *infos, char **params, char *last_pwd);
int exec_built_in(infos_t *infos, int built_in_nb,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_t *));
int execute_command(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN + 1])(infos_t *));
int handle_pipe(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *), char **input);
int status_code(int status);
int is_built_in_command(infos_t *infos, char *command);
int exec_with_path(infos_t *infos);
char *save_redirection(infos_t *infos, char *input);
int is_redirection(infos_t *infos, char *str);
void handle_redirection(infos_t *infos, int pipe_fd[2]);
int is_num(char str);
int is_not_num(char str);
int is_alpha(char str);

history_t *add_to_history(infos_t *infos, char *command);
int history_func(infos_t *infos);
int history(infos_t *infos, char *command);
int my_strn_is_num(char *str, int n);
int my_strn_is_letter(char *str, int n);
int my_getnbr(char *str);
void my_putnbr(int nb);
int n_history(infos_t *infos, char *command);
int last_history(infos_t *infos, char *command);
int n_history_before(infos_t *infos, char *command);
int history_with_string(infos_t *infos, char *command);
int n_history_args(infos_t *infos, char *command);
void strn_replace(infos_t *infos, char *replace, char *to_replace);
int parse_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *));
int process_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *));
int check_pipe(infos_t *infos, char *input);
char **split_by_parentheses(char *str);
int set_func(infos_t *infos);
int tab_len(char **tab);
char *str_insert_and_replace(char *str, char *insert, int start, int end);
env_var_t *get_var(infos_t *infos, char *var_name);
int last_history_args(infos_t *infos, char *command);
int all_history_args(infos_t *infos, char *command);
int first_history_args(infos_t *infos, char *command);
void save_last_command_in_var(infos_t *infos, char *tmp);
int change_variable(infos_t *infos);
char **splitforpipe(char *str, char *separators);
char **shsplit(const char *str);
int is_space(char character);
int backtick(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *));
void backtick_redirection(infos_t *infos, int pipe_fd[2]);
char *backtick_red(infos_t *infos, int pipe_fd[2]);

void check_jobs(infos_t *infos, char ***command, int i);
void realloc_command(infos_t *infos, char ***command, int i,
    char **new_command);

void start_a_job(infos_t *infos);
void delete_jobs(infos_t *infos, job_t *job);
void check_jobs_end(infos_t *infos);
void finish_jobs(infos_t *infos, job_t *job, int status);

int fg_func(infos_t *infos);
int bg_func(infos_t *infos);

typedef int (*command_func_t)(infos_t *, char *);

typedef struct {
    char *command_str;
    command_func_t func;
} command_mapping_t;

extern command_mapping_t history_command[];

typedef struct history_args_s {
    infos_t *infos;
    char *token;
    int current_id;
    int start_id;
    int end_id;
    char *args;
} history_args_t;

typedef struct shsplit_s {
    char *str;
    int num_tokens;
    int current_token_size;
    char quote_char;
    char **tokens;
    int token_index;
} shsplit_t;

void process_string(shsplit_t *shsplit);
void shsplit2(shsplit_t *shsplit);

void get_cwd(infos_t *infos);

int alias_func(infos_t *infos);
int unalias_func(infos_t *infos);
char *delete_half_circle(char *str);
int find_alias(infos_t *infos, char *command);
void add_alias(infos_t *infos);

int file_rc(infos_t *infos, int (*built_in_commands[NB_BUILT_IN])(infos_t *));
int process_input(infos_t *infos,
    int (*built_in_commands[NB_BUILT_IN])(infos_t *));

#endif /* SH_H_ */
