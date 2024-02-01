#include "../../inc/utils.h"

bool    isnum(char * str) {

    if (!str || !str[0])
        return false;
    if (str[0] == '-' || str[0] == '+')
        str++;

    for (size_t i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;

    return true;
}