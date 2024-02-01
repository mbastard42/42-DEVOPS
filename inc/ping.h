#pragma once

#include "utils.h"
#include <limits.h>

//  DATA.C

typedef struct s_config {

    int     error;
    char *  host;

    //  Options controlling ICMP request types:

    bool    address;
    bool    echo;
    bool    mask;
    bool    timestamp;
    char *  type;               // -t

    //  Options valid for all request types:

    int     count;              // -c
    bool    debug;              // -d
    int     interval;           // -i
    bool    numeric;            // -n
    bool    ignore_routing;     // -r
    int     ttl;
    int     tos;                // -T
    bool    verbose;            // -v
    int     timeout;            // -w
    int     linger;             // -W

    //  Options valid for --echo requests:

    bool    flood;              // -f
    char *  ip_timestamp;
    int     preload;            // -l
    int     pattern;            // -p
    bool    quit;               // -q
    bool    route;              // -R
    int     size;               // -s

    //  Other options

    bool    help;               // -?
    bool    usage;
    bool    version;            // -V

}   t_config;

t_config *  new_config(void);
void        del_config(t_config * config);
void        print_config(t_config * config);

//  INPUT/*.C

char **     lexer(int argc, char ** argv);
void        checker(t_config * config, char ** tokens);
void        parser(t_config * config, char ** tokens);

//  PING/PING.C

void        ping(t_config * config, FILE * stream);
