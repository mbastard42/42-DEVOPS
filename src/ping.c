#include "../inc/ping.h"

void ping(t_config * config, FILE * stream) {

    (void) stream;
    if (!config->host) {
        fprintf(stderr, "ft_ping: missing host operand\n");
        config->error = fprintf(stderr, "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
    }

}