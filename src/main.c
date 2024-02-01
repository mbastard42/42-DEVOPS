#include "../inc/ping.h"

//  remove main.c and input folder to use ping in a c project

int main(int argc, char ** argv) {

    FILE *      stream = stdout;
    t_config *  config = new_config();
    char **     tokens = lexer(argc, argv);

    checker(config, tokens);
    // parser(config, tokens);
    freetab(tokens);

    if (!config->error)
        ping(config, stream);

    int error = config->error;
    del_config(config);

    return error;
}