#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

void printColoredText(int colorCode, const char *text)
{
    if (!colorCode || !text)
    {
        int colorRed = COLOR_RED;
        printf("\x1b[%dm%s\x1b[0m\n", colorRed, "Incomplete arguments, color-code or text missing\n");
        exit(EXIT_FAILURE);
    }
    printf("\x1b[%dm%s\x1b[0m\n", colorCode, text);
}
