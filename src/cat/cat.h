#include <stdio.h>
#include <string.h>
#include <getopt.h>

    //  -b      Number the non-blank output lines, starting at 1.

    //  -e      Display non-printing characters (see the -v option), and display
    //          a dollar sign (`$') at the end of each line.

    //  -n      Number the output lines, starting at 1.

    //  -s      Squeeze multiple adjacent empty lines, causing the output to be
    //          single spaced.


    //  -t      Display non-printing characters (see the -v option), and display
    //          tab characters as `^I'

void cat(char* filename, int flags[6]);
int parse(int argc, char** argv, int flags[6], int* file_id);
