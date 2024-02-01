#include "../../inc/ping.h"

static char ** flags = (char *[]) {
    "--address",
    "--count",
    "--debug",
    "--echo",
    "--flood",
    "--help",
    "--ignore-routing",
    "--interval",
    "--ip-timestamp",
    "--linger",
    "--mask",
    "--numeric",
    "--pattern",
    "--preload",
    "--quit",
    "--route",
    "--size",
    "--timestamp",
    "--timeout",
    "--tos",
    "--ttl",
    "--type",
    "--usage",
    "--verbose",
    "--version",
    "--size",
    NULL
};
static char ** bools = (char *[]) {
    "--address",
    "--debug",
    "--echo",
    "--flood",
    "--help",
    "--ignore-routing",
    "--mask",
    "--numeric",
    "--quit",
    "--route",
    "--timestamp",
    "--verbose",
    "--version",
    NULL
};
static char ** vals = (char *[]) {
    "--count",
    "--interval",
    "--ip-timestamp",
    "--linger",
    "--pattern",
    "--preload",
    "--size",
    "--timeout",
    "--tos",
    "--ttl",
    "--type",
    NULL
};

static void specific_checker(t_config * config, char * arg) {

    char *  arg_start = ft_strchr(arg, '=');
    size_t  arg_len = ft_sublen(arg, '=');

    for (size_t i = 0; !config->error && bools[i]; i++) { // bool options

        if (!ft_strncmp(arg, bools[i], arg_len) && arg_start) { // bool option with argument

            printf("ft_ping: option '%s' doesn't allow an argument\n", bools[i]);
            config->error = printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
        }
    }

    for (size_t i = 0; !config->error && vals[i]; i++) { // value options

        if (!ft_strncmp(arg, vals[i], arg_len)) {

            if (!arg_start) { // value option without argument

                printf("ft_ping: option '%s' requires an argument\n", vals[i]);
                config->error = printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
            }

            else if (i == 0) { // --count

                for (size_t j = arg_len + 1; !config->error && arg[j]; j++) // --count=text
                    if ((j == arg_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > arg_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % printf("ft_ping: invalid value: ('%s' near '%s')\n", arg_start + 1, &arg[j]);
            }

            else if (i == 1) { // --interval

                for (size_t j = arg_len + 1; !config->error && arg[j]; j++) // --interval=text
                    if ((j == arg_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > arg_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % printf("ft_ping: invalid value: ('%s' near '%s')\n", arg_start + 1, &arg[j]);

                if (!atoi(arg_start + 1)) // --interval= // --interval=0
                    config->error = 1 % printf("ft_ping: option value too small: %s\n", arg_start + 1);
            }

            else if (i == 2) { // --ip-timestamp

                if (ft_strcmp(arg_start + 1, "tsonly") && ft_strcmp(arg_start + 1, "tsaddr")) // --ip-timestamp=text
                    config->error = 1 % printf("ft_ping: unsupported timestamp type: %s\n", arg_start + 1);
            }

            else if (i == 3) { // --linger

                for (size_t j = arg_len + 1; !config->error && arg[j]; j++) // --linger=text
                    if ((j == arg_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > arg_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % printf("ft_ping: invalid value: ('%s' near '%s')\n", arg_start + 1, &arg[j]);
                
                if (ft_strlen(arg_start + 1) > 10 || (ft_strlen(arg_start + 1) == 10 && *(arg_start + 1) == '2' && atoi(arg_start + 2) > 147483647))
                    config->error = 1 % printf("ft_ping: option value too big: %s\n", arg_start + 1);

                if (atoi(arg_start + 1) < 1) // --linger= // --linger=<0
                    config->error = 1 % printf("ft_ping: option value too small: %s\n", arg_start + 1);
            }

            else if (i == 4) {


            }
        }
    }
}

static void minimized_checker(t_config * config, char * arg) {

    (void)config;
    (void)arg;
}

void checker(t_config * config, char ** tokens) {

    for (int i = 1; !config->error && tokens && tokens[i]; i++) {

        if (tokens[i][1] == '-') // host operand
            minimized_checker(config, tokens[i]);

        int match = 0;

        if (tokens[i][0] != '-' || (tokens[i][0] == '-' && !tokens[i][1])) // host operand
            continue;

        for (size_t j = 0; flags[j]; j++)
            if (!ft_strncmp(tokens[i], flags[j], ft_sublen(tokens[i], '=')))
                match++;

        if (!match) { // unrecognized option

            printf("ft_ping: unrecognized option '%s'\n", tokens[i]);
            config->error = printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");

        } else if (match > 1) { // ambiguous option

            printf("ft_ping: option '%s' is ambiguous; possibilities:", tokens[i]);

            for (size_t j = 0; flags[j]; j++)
                if (!ft_strncmp(tokens[i], flags[j], ft_strlen(tokens[i])))
                    printf(" '%s'", flags[j]);

            config->error = printf("\nTry 'ft_ping --help' or 'ft_ping --usage' for more information.\n") - 1;
        }

        if (!config->error)
            specific_checker(config, tokens[i]);
    }
}
