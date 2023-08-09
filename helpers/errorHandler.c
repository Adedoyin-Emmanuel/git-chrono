#include <stdlib.h>
#include <stdio.h>

void throwError(const char *text);

void throwError(const char *text)
{

    if (!text)
    {
        printf("\x1b[%dm%s\x1b[0m\n", 31, "Incomplete arguments, text missing\n");
        exit(EXIT_FAILURE);
    }
    printf("\x1b[%dm%s\x1b[0m\n", 31, text);
    exit(EXIT_FAILURE);
}
