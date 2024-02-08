#include "../../inc/ping.h"

static char ** flags = (char *[]) {
    "--address",
    "--count",
    "--debug",
    "--echo",
    "--flood",
    "--help",
    "--interval",
    "--ignore-routing",
    "--ip-timestamp",
    "--linger",
    "--mask",
    "--numeric",
    "--preload",
    "--pattern",
    "--quit",
    "--route",
    "--size",
    "--timestamp",
    "--type",
    "--tos",
    "--ttl",
    "--timeout",
    "--usage",
    "--verbose",
    "--version",
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

    size_t  flag_len = ft_sublen(arg, '=');
    char *  val = ft_strchr(arg, '=') ? ft_strchr(arg, '=') + 1 : NULL;
    size_t  val_len = ft_strlen(val);
    int     converted = ft_atoi(val);

    for (size_t i = 0; !config->error && bools[i]; i++) { // bool options

        if (!ft_strncmp(arg, bools[i], flag_len) && ft_strchr(arg, '=')) { // bool option with argument

            fprintf(stderr, "ft_ping: option '%s' doesn't allow an argument\n", bools[i]);
            config->error = fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
        }
    }

    for (size_t i = 0; !config->error && vals[i]; i++) { // value options

        if (!ft_strncmp(arg, vals[i], flag_len)) {

            if (!ft_strchr(arg, '=')) { // value option without argument

                fprintf(stderr, "ft_ping: option '%s' requires an argument\n", vals[i]);
                config->error = fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
            }

            else if (i == 0) { // --count

                for (size_t j = flag_len + 1; !config->error && arg[j]; j++) // --count=text
                    if ((j == flag_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > flag_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % fprintf(stderr, "ft_ping: invalid value: ('%s' near '%s')\n", val, &arg[j]);
            }

            else if (i == 1) { // --interval

                for (size_t j = flag_len + 1; !config->error && arg[j]; j++) // --interval=text
                    if ((j == flag_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > flag_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % fprintf(stderr, "ft_ping: invalid value: ('%s' near '%s')\n", val, &arg[j]);

                if (!converted) // --interval= // --interval=0
                    config->error = 1 % fprintf(stderr, "ft_ping: option value too small: %s\n", val);
            }

            else if (i == 2) { // --ip-timestamp

                if (ft_strcmp(val, "tsonly") && ft_strcmp(val, "tsaddr")) // --ip-timestamp=!(tsonly|tsaddr)
                    config->error = 1 % fprintf(stderr, "ft_ping: unsupported timestamp type: %s\n", val);
            }

            else if (i == 3) { // --linger

                for (size_t j = flag_len + 1; !config->error && arg[j]; j++) // --linger=text
                    if ((j == flag_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > flag_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % fprintf(stderr, "ft_ping: invalid value: ('%s' near '%s')\n", val, &arg[j]);
                
                if (val_len > 10 || !isnum(val)) // --linger=x>2147483647
                    config->error = 1 % fprintf(stderr, "ft_ping: option value too big: %s\n", val);
                else if (converted < 1 || *val == '-') // --linger= // --linger=x<1
                    config->error = 1 % fprintf(stderr, "ft_ping: option value too small: %s\n", val);
            }

            else if (i == 4) { // --pattern
            
                if (!ishex(val)) { // --pattern=hex
 
                    size_t j = 0;

                    if (*(val + j) == '0' && (*(val + 2 + j) == 'x' || *(val + 2 + j) == 'X'))
                        j += 2;
                    if (*(val + j) == '-' || *(val + j) == '+')
                        j++;
                    for (; !config->error && *(val + j) ; j++)
                        if (!strchr("0123456789abcdefABCDEF", *(val + j)))
                            config->error = 1 % fprintf(stderr, "ft_ping: error in pattern near %s\n", val + j);
                }
            }

            else if (i == 5) { // --preload

                for (size_t j = flag_len + 1; !config->error && arg[j]; j++) // --preload=text
                    if ((j == flag_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > flag_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % fprintf(stderr, "ft_ping: invalid preload value (%s)\n", val);
                
                if (val_len > 10 || !isnum(val)) // --preload=x>2147483647
                    config->error = 1 % fprintf(stderr, "ft_ping: invalid preload value (%s)\n", val);
                else if (converted < 0 || *val == '-') // --preload= // --preload=x<0
                    config->error = 1 % fprintf(stderr, "ft_ping: invalid preload value (%s)\n", val);

            }

            else if (i == 6) { // --size

                for (size_t j = flag_len + 1; !config->error && arg[j]; j++) // --size=text
                    if ((j == flag_len + 1 && !ft_strchr("-+0123456789", arg[j])) || (j > flag_len + 1 && !ft_strchr("0123456789", arg[j])))
                        config->error = 1 % fprintf(stderr, "ft_ping: invalid value: ('%s' near '%s')\n", val, &arg[j]);
                
                if (converted > 65399) // --size=x>65399
                    config->error = 1 % fprintf(stderr, "ft_ping: option value too big: %s\n", val);
                else if (converted < 0 || *val == '-') // --size= // --size=x<0
                    config->error = 1 % fprintf(stderr, "ft_ping: option value too big: %s\n", val);

            }

            else if (i == 7) { // --timeout

            }

            else if (i == 8) { // --tos}

            }

            else if (i == 9) { // --ttl}

            }

            else if (i == 10) { // --type}

            }
        }
    }
}

static void minimized_checker(t_config * config, char * arg) {

    (void)config;
    (void)arg;
}

void checker(t_config * config, char ** tokens) {

    for (int i = 0; !config->error && tokens && tokens[i]; i++) {

        int match = 0;

        if (tokens[i][0] != '-' || (tokens[i][0] == '-' && !tokens[i][1])) // host operand
            continue;

        if (tokens[i][1] != '-') {
            minimized_checker(config, tokens[i]);
            continue;
        }

        for (size_t j = 0; flags[j]; j++)
            if (!ft_strncmp(tokens[i], flags[j], ft_sublen(tokens[i], '=')))
                match++;

        if (!match) { // unrecognized option

            fprintf(stderr, "ft_ping: unrecognized option '%s'\n", tokens[i]);
            config->error = fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");

        } else if (match > 1) { // ambiguous option

            fprintf(stderr, "ft_ping: option '%s' is ambiguous; possibilities:", tokens[i]);

            for (size_t j = 0; flags[j]; j++)
                if (!ft_strncmp(tokens[i], flags[j], ft_strlen(tokens[i])))
                    fprintf(stderr, " '%s'", flags[j]);
            fprintf(stderr, "\n");

            config->error = fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
        }

        if (!config->error)
            specific_checker(config, tokens[i]);
    }
}
