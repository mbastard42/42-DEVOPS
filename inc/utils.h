#pragma once

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//  UTILS/STRING.C

size_t  ft_sublen(char * str, char c);
size_t  ft_strlen(char * str);
char *  ft_strchr(char * str, char c);
int     ft_strncmp(char * s1, char * s2, size_t n);
int     ft_strcmp(char * s1, char * s2);
char *  ft_strdup(char * str);
char *  ft_strcpy(char * dst, char * src);

bool    isnum(char * str);
void    freetab(char ** tab);
void *  nerr(int code, char * message);