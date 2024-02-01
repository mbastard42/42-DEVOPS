#include "../../inc/ping.h"

static char ** flags = (char *[]) {
    "--address",
    "-c",
    "--count",
    "-d",
    "--debug",
    "--echo",
    "-f",
    "--flood",
    "-?",
    "--help",
    "-r",
    "--ignore-routing",
    "-i",
    "--interval",
    "--ip-timestamp",
    "-W",
    "--linger",
    "--mask",
    "-n",
    "--numeric",
    "-p",
    "--pattern",
    "-l",
    "--preload",
    "-q",
    "--quit",
    "-R",
    "--route",
    "-s",
    "--size",
    "--timestamp",
    "-w",
    "--timeout",
    "-T",
    "--tos",
    "--ttl",
    "-t",
    "--type",
    "--usage",
    "-v",
    "--verbose",
    "-V",
    "--version",
    NULL
};

char ** lexer(int argc, char ** argv) {

    char ** tokens;
    int     len = argc;

    for (int i = 1; i < argc; i++)
        for (int j = 0; flags[j]; j++)
            if (!ft_strncmp(argv[i], flags[j], ft_sublen(argv[i], '='))) // argv[i] is a valid option
                if ((flags[j][1] != '-' || (flags[j][1] == '-' && !ft_strchr(argv[i], '='))) && !ft_strchr(argv[i], '=') && i < argc - 1) // argv[i + 1] is argv[i]'s argument
                    len--;

    if (!(tokens = calloc(len, sizeof(char *))))
        return nerr(ENOMEM, "lexer()");

    for (int i = 1, tab = 0; i < argc; i++, tab++) {

        for (int j = 0; flags[j]; j++) {

            if (!ft_strncmp(argv[i], flags[j], ft_sublen(argv[i], '='))) { // argv[i] is a valid option

                if (flags[j][1] != '-' && i < argc - 1) { // (-flag) argv[i + 1] is argv[i]'s argument

                    if (!(tokens[tab] = calloc(ft_strlen(argv[i]) + ft_strlen(argv[i + 1]) + 1, sizeof(char))))
                        return nerr(ENOMEM, "lexer()");
                    ft_strcpy(tokens[tab], argv[i]);
                    ft_strcpy(tokens[tab] + ft_strlen(argv[i]), argv[i + 1]);
                    i++;
                }
                else if (flags[j][1] == '-' && i < argc - 1 && !ft_strchr(argv[i], '=')) { // (--flag) argv[i + 1] is argv[i]'s argument

                    if (!(tokens[tab] = calloc(ft_strlen(argv[i]) + ft_strlen(argv[i + 1]) + 2, sizeof(char))))
                        return nerr(ENOMEM, "lexer()");
                    ft_strcpy(tokens[tab], argv[i]);
                    tokens[tab][ft_strlen(argv[i])] = '=';
                    ft_strcpy(tokens[tab] + ft_strlen(argv[i]) + 1, argv[i + 1]);
                    i++;
                }
            }
        }
        if (!tokens[tab])
            tokens[tab] = ft_strdup(argv[i]);
    }

    return tokens;
}