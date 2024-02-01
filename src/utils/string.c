#include "../../inc/utils.h"

size_t  ft_sublen(char * str, char c) {

    size_t len = 0;

    while (str && str[len] && str[len] != c)
        len++;

    return len;
}

size_t  ft_strlen(char * str) {

    return ft_sublen(str, 0);
}

char *  ft_strchr(char * str, char c) {

    if (!str || !*str || ft_strlen(str) == ft_sublen(str, c))
        return NULL;

    return str + ft_sublen(str, c);
}

int     ft_strncmp(char * s1, char * s2, size_t n) {

    for (size_t i = 0; i < n; i++) {

        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        if (!s1[i])
            return 0;
    }

    return 0;
}

int     ft_strcmp(char * s1, char * s2) {

    return ft_strncmp(s1, s2, ft_strlen(s1) + 1);
}

char *  ft_strdup(char * str) {

    char * dup = malloc(ft_strlen(str) + 1);

    if (!dup)
        return nerr(ENOMEM, "ft_strdup()");

    for (size_t i = 0; str[i]; i++)
        dup[i] = str[i];
    dup[ft_strlen(str)] = '\0';

    return dup;
}

char *  ft_strcpy(char * dst, char * src) {

    for (size_t i = 0; dst && src && src[i]; i++)
        dst[i] = src[i];

    return dst;
}