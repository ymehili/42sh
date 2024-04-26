/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** is_space
*/

#include "../../include/sh.h"

int is_space(char character)
{
    return character == ' ' || character == '\t' || character == '\n';
}
