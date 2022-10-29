#include "cat.h"

void cat(char* filename, int flags[5]) {
    FILE *file = fopen(filename, "r");
    char c = 0;
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
        
        if (!(flags[3] && empty_flag && c == '\n'))
            printf("%c", c);
        if (c == '\n' && !empty_test) {
            empty_test = 1;
        } else if (c == '\n' && empty_test) {
            empty_flag = 1;
        } else
            empty_test = 0, empty_flag = 0;
        
        
        
        c = fgetc(file);
    }
} 
int main() {
    int flags[] = {0,0,0,1,0};
    cat("/Users/knothulk/test.txt", flags);
    return 0;
}