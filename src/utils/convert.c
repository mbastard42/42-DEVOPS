#include "../../inc/utils.h"

int     ft_atoi(char * str) {

    if (!str || !str[0] || !isnum(str))
        return 0;

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }

    if (ft_strlen(str) > 10 || (ft_strlen(str) == 10 && *str == '2' && ft_atoi(str + 1) > 147483647))
        return 0;

    int res = 0;
    while (*str)
        res = res * 10 + *str++ - '0';

    return res * sign;
}