/*
** EPITECH PROJECT, 2024
** Delivery
** File description:
** line_cwd
*/

#include "../include/sh.h"

void get_cwd(infos_t *infos)
{
    env_var_t *tmp = infos->env_linked_ls;

    infos->line_cwd = NULL;
    infos->line_cwd = "-> ";
    while (tmp != NULL) {
        if (my_strcmp(tmp->name, "PWD") == 0) {
            infos->line_cwd = my_strcat(infos->line_cwd, "\033[96m");
            infos->line_cwd = my_strcat(infos->line_cwd, tmp->val);
            infos->line_cwd = my_strcat(infos->line_cwd, "\033[0m");
            break;
        }
        tmp = tmp->next;
    }
    infos->line_cwd = my_strcat(infos->line_cwd, " > ");
}