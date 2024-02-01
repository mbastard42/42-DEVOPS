#include "../../inc/utils.h"

void    freetab(char ** tab) {

    for (size_t i = 0; tab && tab[i]; i++)
        free(tab[i]);
    if (tab)
        free(tab);
}

void *  nerr(int code, char * message) {

    errno = code;
    printf("%s: %s\n", message, strerror(errno));
    return NULL;
}