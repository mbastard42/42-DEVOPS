#include "../../inc/utils.h"

bool    isnum(char * str) {

    if (!str || !str[0])
        return false;
    if (str[0] == '-' || str[0] == '+')
        str++;
    
    if (ft_strlen(str) > 10 || (ft_strlen(str) == 10 && *str == '2' && ft_atoi(str + 1) > 147483647))
        return false;

    for (size_t i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;

    return true;
}

bool    ishex(char * str) {

    if (!str || !*str)
        return false;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        str += 2;
    if (*str == '-' || *str == '+')
        str++;

    while (*str)
        if (!strchr("0123456789abcdefABCDEF", *str++))
            return false;

    return true;
}