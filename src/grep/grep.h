#include <stdio.h>
#include <regex.h>
#include <getopt.h>
#include <string.h>
#define LINEMAX 101
typedef struct node {
    int line;
    char data[LINEMAX];
    struct node* next;
} node;

typedef struct flags {
    int e = 0;
    int i = 0;
    int v = 0;
    int c = 0;
    int l = 0;
    int n = 0;
    int h = 0;
    int s = 0;
    int f = 0;
    int o = 0;
} flags;

node* init(int line, char data[LINEMAX]);
node* add(node* head, int line, char data[LINEMAX]);
void clear_list(node* head);
int count(node* head);
int parse(int argc, char** argv, flags* flags, int* file_id);
void grep(char* filename, char* find, flags flags);
