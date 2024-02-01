#include "../inc/ping.h"

t_config *  new_config() {

    t_config * config;

    if (!(config = malloc(sizeof(t_config))))
        return nerr(ENOMEM, "new_config()");

    config->error = 0;
    config->host = NULL;

    config->address = false;
    config->echo = false;
    config->mask = false;
    config->timestamp = false;
    config->type = NULL;

    config->count = -1;
    config->debug = false;
    config->interval = -1;
    config->numeric = false;
    config->ignore_routing = false;
    config->ttl = -1;
    //config->tos = ;
    config->verbose = false;
    config->timeout = -1;
    config->linger = -1;

    config->flood = false;
    // config->ip_timestamp = ;
    config->preload = -1;
    config->pattern = -1;
    config->quit = false;
    config->route = false;
    config->size = -1;

    config->help = false;
    config->usage = false;
    config->version = false;

    return config;
}

void    del_config(t_config * config) {

    if (config) {

        if (config->host)
            free(config->host);
        if (config->type)
            free(config->type);
        free(config);
    }
}

void    print_config(t_config * config) {

    if (config) {

        printf("error: %d\n", config->error);
        printf("host: %s\n", config->host);

        printf("address: %s\n", config->address ? "true" : "false");
        printf("echo: %s\n", config->echo ? "true" : "false");
        printf("mask: %s\n", config->mask ? "true" : "false");
        printf("timestamp: %s\n", config->timestamp ? "true" : "false");
        printf("type: %s\n", config->type);

        printf("count: %d\n", config->count);
        printf("debug: %s\n", config->debug ? "true" : "false");
        printf("interval: %d\n", config->interval);
        printf("numeric: %s\n", config->numeric ? "true" : "false");
        printf("ignore_routing: %s\n", config->ignore_routing ? "true" : "false");
        printf("ttl: %d\n", config->ttl);
        //printf("tos: %d\n", config->tos);
        printf("verbose: %s\n", config->verbose ? "true" : "false");
        printf("timeout: %d\n", config->timeout);
        printf("linger: %d\n", config->linger);

        printf("flood: %s\n", config->flood ? "true" : "false");
        //printf("ip_timestamp: %d\n", config->ip_timestamp);
        printf("preload: %d\n", config->preload);
        printf("pattern: %d\n", config->pattern);
        printf("quit: %s\n", config->quit ? "true" : "false");
        printf("route: %s\n", config->route ? "true" : "false");
        printf("size: %d\n", config->size);

        printf("help: %s\n", config->help ? "true" : "false");
        printf("usage: %s\n", config->usage ? "true" : "false");
        printf("version: %s\n", config->version ? "true" : "false");
    }
}