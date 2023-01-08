#include "grep.h"

node* init(int line, char data[LINEMAX]) {
    node *head = malloc(sizeof(node));
    strcpy(head -> data, data);
    head -> line = line;
    head -> next = NULL;
    return head;
}
node* add(node* head, int line, char data[LINEMAX]) {
    if (head == NULL)
        return init(line, data);
    node *temp = head;
    while (temp -> next != NULL)
        temp = temp -> next;
    temp -> next = init(line, data);
    return head;
}
void clear_list(node* head) {
    if (head == NULL)
        return;
    node* temp = head -> next;
    while (head != NULL) {
        free(head);
        head = temp;
        temp = temp -> next;
    }
}
int count(node* head) {
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head -> next;
    }
    return cnt;
}

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
                flags -> o = 0;
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
                if (!(flags->v))
                    flags -> o = 1;
                break;
            default:
                fprintf(stderr, "Wrong param");
                return 1;
        }
        i++;
    }
    *file_id = optind + 1;
    return 0;
}

void grep(char* filename, char* find, flags flags) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        if (!(flags.s))
            fprintf(stderr, "grep: %s: No such file or directory", filename);
        fclose(file);
        return;
    }
    node *head = NULL;
    int line_counter = 1;
    char line[LINEMAX];

    if (flags.i) {
        char* (*str_found)(const char*, const char*) = strstr;
    }
    while(!feof(file)) {
        fgets(line, LINEMAX, file);
        

    }
    // out
    if (flags.c || flags.l) {
        if (flags.c) {
            if (!flags.h)
                printf("%s:", filename);
            printf("%d\n", count(head));
        }
        if (flags.l && count(head) > 0)
            printf("%s\n", filename);
    }
    else {
        node* temp = head;
        while(temp != NULL) {
            if (!flags.h)
                printf("%s:", filename);
            if(flags.n)
                printf("%d:", temp -> line);
            printf("%s\n", temp -> data);
            temp = temp -> next;
        }
    }
    clear_list(head);
    head = NULL;
    fclose(file);
} 
/*
-e Шаблон
-i Игнорирует различия регистра. //strcasestr
-v Инвертирует смысл поиска соответствий.
-f file Получает регулярные выражения из файла.
-o Печатает только совпадающие (непустые) части совпавшей строки.


-c
Выводит только количество совпадающих строк.

-l
Выводит только совпадающие файлы.

-n
Предваряет каждую строку вывода номером строки из файла ввода.

-h
Выводит совпадающие строки, не предваряя их именами файлов.

-s
Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.
*/