// This software is in the public domain.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char data[30000] = {0};

void usage(void) {
    fprintf(stderr, "usage: nfck [file]\n");
    exit(2);
}

void nfck(void) {
    char array[30000] = {0};
    char *p = array;

    int loop = 0;

    char *pc = data;
    while (*pc) {
        switch (*pc) {
        case ')':
            ++p;
            break;
        case '(':
            --p;
            break;
        case '*':
            ++(*p);
            break;
        case '/':
            --(*p);
            break;
        case '!':
            putchar(*p);
            break;
        case '?':
            *p = getchar();
            break;
        case '{':
            if (!*p)
                while (*(++pc)) {
                    if (*pc == '}' && loop == 0)
                        break;
                    if (*pc == '{')
                        ++loop;
                    else if (*pc == '}')
                        --loop;
                };
            break;
        case '}':
            if (*p)
                while (*(--pc)) {
                    if (*pc == '{' && loop == 0)
                        break;
                    if (*pc == '}')
                        ++loop;
                    else if (*pc == '{')
                        --loop;
                };
            break;
        default:
            break;
        }
        pc++;
    }
}

int main(int argc, const char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    char *pc = data;
    int ch;

    if (argc == 1)
        usage();

    if (file == NULL) {
         printf("error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
        case '(':
        case ')':
        case '*':
        case '/':
        case '!':
        case '?':
        case '{':
        case '}':
            *(pc++) = ch;
        }
    }

    fclose(file);

    nfck();

    return EXIT_SUCCESS;
}
