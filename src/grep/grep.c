#include "grep.h"

int parse(int argc, char** argv, flags* flags, int* file_id) {
        int param_count = 0;
    for (; param_count + 1 < argc && argv[param_count + 1][0] == '-'; param_count++);
    const char* short_options = "eivclnhsfo";
    const struct option long_options[] = {
        {"line-number", no_argument, NULL, 'n'},
        {"file", required_argument, NULL, 'f'},
        {"no-filename", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0},
        {"count", no_argument, NULL, 'c'},
        {"ignore-case", no_argument, NULL, 'i'},
        {"files-with-matches", no_argument, NULL, 'f'},
        {"only-matching", no_argument, NULL, 'o'},
        {"no-messages", no_argument, NULL, 's'},
        {"invert-match", no_argument, NULL, 'v'},
    };
    int rez, option_index, i = 0;
    opterr = 0;
    optind = 1;
    while (i < param_count && (rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (rez) {
            case 'e':
                flags -> e = 1;
                break;
            case 'i':
                flags -> i = 1;
                break;
            case 'v':
                flags -> v = 1;
                break;
            case 'c':
                flags -> c = 1;
                break;
            case 'l':
                flags -> l = 1;
                break;
            case 'n':
                flags -> n = 1;
                break;
            case 'h':
                flags -> h = 1;
                break;
            case 's':
                flags -> s = 1;
                break;
            case 'f':
                flags -> f = 1;
                break;
            case 'o':
                flags -> o = 1;
                break;
            default:
                fprintf(stderr, "Wrong param");
                return 1;
        }
        i++;
    }
    *file_id = optind;
    return 0;
}

void grep(char* filename, char* find, flags flags) {
    
}
