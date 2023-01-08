#include <stdio.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#define LINEMAX 101
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
int parse(int argc, char** argv, flags* flags, int* file_id);
void grep(char* filename, char* find, flags flags);
