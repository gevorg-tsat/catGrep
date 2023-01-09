#include "grep.h"

int main(int argc, char* argv[]) {
    flags flags = {0};
    int file_id = 0;
    char pattern[LINEMAX];
    char pattern_file[LINEMAX * _LINE_AMOUNT_MAX_];
    if (parse(argc, argv, &flags, &file_id, pattern, pattern_file))
        return 1;
    if (argc - file_id == 1)
        flags.h = 1;
    for (int i = file_id; i < argc; i++) {
        grep(argv[file_id], pattern, flags);
        if (flags.f)
            grep(argv[file_id], pattern_file, flags);
    }
    return 0;
}

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

int read_pattern_file(char* filename, char pattern[LINEMAX * _LINE_AMOUNT_MAX_]) {
    char line[LINEMAX];
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "grep: %s: No such file or directory", filename);
        return 1;
    }
    while(!feof(file)) {
        fgets(line, LINEMAX, file);
        strcat(pattern, line);
        strcat(pattern, "|");
    }
    fclose(file);
    return 0;
}

int parse(int argc, char** argv, flags* flags, int* file_id, char pattern[LINEMAX], char pattern_file[LINEMAX * _LINE_AMOUNT_MAX_]) {
    const char* short_options = "e:ivclnhsf:o";
    const struct option long_options[] = {{NULL, 0, NULL, 0}};
    int rez, option_index, i = 0;
    opterr = 0;
    optind = 1;
    pattern[0]='\0';
    pattern_file[0]='\0';
    while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (rez) {
            case 'e':
                flags -> e = 1;
                strcat(pattern, optarg);
                strcat(pattern_file, "|");
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
                read_pattern_file(optarg, pattern_file);
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
    if (!(flags -> f) && !(flags -> e)) {
        strcat(pattern, argv[optind]);
        optind++;
    }
    *file_id = optind;
    return 0;
}


void grep(char* filename, char* pattern, flags flags) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        if (!(flags.s))
            fprintf(stderr, "grep: %s: No such file or directory", filename);
        return;
    }
    node *head = NULL;
    int line_counter = 1;
    char line[LINEMAX];
    regex_t regex;
    if (flags.i)
        regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    else
        regcomp(&regex, pattern, REG_EXTENDED);
    regmatch_t match;
    while(!feof(file)) {
        fgets(line, LINEMAX, file);
        int not_found = regexec(&regex, line, 1, &match, 0);
        if ((!not_found && !flags.v) || (not_found && flags.v)) {
            if (!flags.o || flags.v)
                head = add(head, line_counter, line);
            else {
                while (!not_found) {
                    char mat[LINEMAX];
                    int i = 0;
                    while (i != match.rm_eo - match.rm_so) {
                        mat[i] = line[match.rm_so + i];
                        i++;
                    }
                    mat[i] = '\0';
                    head = add(head, line_counter, mat);
                    not_found = regexec(&regex, line + match.rm_eo, 1, &match, 0);
                }
            }
        }
        line_counter++;
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
    //clear_list(head);
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