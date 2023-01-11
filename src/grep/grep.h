#include <stdio.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#define LINEMAX 501
#define _LINE_AMOUNT_MAX_ 100
typedef struct node {
    int line;
    char data[LINEMAX];
    struct node* next;
} node;

typedef struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} flags;

node* init(int line, char data[LINEMAX]);
node* add(node* head, int line, char data[LINEMAX]);
void clear_list(node* head);
int count(node* head);
int parse(int argc, char** argv, flags* flags, int* file_id, char pattern[LINEMAX], char pattern_file[LINEMAX * _LINE_AMOUNT_MAX_]);
void grep(char* filename, char* pattern, flags flags);
int read_pattern_file(char* filename, char pattern[LINEMAX * _LINE_AMOUNT_MAX_]);
int linefeed_check(char line[LINEMAX]);
void pattern_fix(char str[LINEMAX + LINEMAX * _LINE_AMOUNT_MAX_]);
void linefeed_ptrn_fix(char str[LINEMAX]);