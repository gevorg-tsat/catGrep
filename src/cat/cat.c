#include "cat.h"

void cat(char* filename, int flags[5]) {
    FILE *file = fopen(filename, "r");
    int c = 0;
    //flags:
    // [0] -b: non empty
    // [1] -e: $ instead of \n
    // [2] -n: all lines
    // [3] -s squeeze empty lines
    // [4] -t ^I instead of tab 
    
    int empty_test = 0, empty_flag = 0;
    c = fgetc(file);
    int lines_counter = 0;
    if ((flags[0] && c!= '\n') || flags[2])
        printf("     %d  ", ++lines_counter);
    while (c != EOF) {
        if (c == EOF)
            return;
        if (flags[2] && empty_test)
            printf("     %d  ", ++lines_counter);
        else if (flags[0] && empty_test && c!='\n')
            printf("     %d  ", ++lines_counter);
        if ((flags[1] || flags[4]) && (c >=0 && c <=31) && c!=10 && c!=9)
            printf("^%c", c + 64);
        else if ((flags[1] || flags[4]) && (c>=128))
            printf("%c", c - 64);
        else if (flags[1] && c == '\n')
            printf("$%c", c);
        else if (flags[4] && c == 9)
            printf("^I");
        else if (!(flags[3] && empty_flag && c == '\n'))
            printf("M-%c", c);
        if (c == '\n' && !empty_test) {
            empty_test = 1;
        } else if (c == '\n' && empty_test) {
            empty_flag = 1;
        } else
            empty_test = 0, empty_flag = 0;
        

        c = fgetc(file);
    }
}

void parse(int argc, char** argv, int flags[5], int* file_id) {
    //flags:
    // [0] -b: non empty
    // [1] -e: $ instead of \n
    // [2] -n: all lines
    // [3] -s squeeze empty lines
    // [4] -t ^I instead of tab 
     	const char* short_options = "beEnstTv";
    const struct option long_options[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", optional_argument, NULL, 'n'},
        {"squeeze-blank", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0}
    };
    int rez, option_index;
    opterr = 0;
    while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1 && !flag) {
        if (rez == 'b') { 
            flags[0] = 1;
            flags[2] = 0;
        } else if (rez == 'e') {
            flags[1] = 1;
            op->v = 1;
        } else if (rez == 'E') {
            op->e = 1;
        } else if (rez == 'T') {
            op->t = 1;
        } else if (rez == 'n') {
            if (op->b == 0)
                op->n = 1;
        } else if (rez == 's') {
            op->s = 1;
        } else if (rez == 't') {
            op->t = 1;
            op->v = 1;
        } else if (rez == 'v') {
            op->v = 1;
        } else {
            fprintf(stderr, "Wrong param");
            flag = 1;
        }
    };
    *file_id = optind;
}

int main() {
    int flags[] = {0,0,0,0,0};
    cat("/Users/knothulk/test.txt", flags);
    return 0;
}