#include "colors.c"

void printSuccessText(const char *text)
{
    short colorGreen = COLOR_GREEN;
    printColoredText(colorGreen, text);
}

void printErrorText(const char *text)
{
    short colorRed = COLOR_RED;
    printColoredText(colorRed, text);
}

void printWarningText(const char *text)
{
    short colorYellow = COLOR_YELLOW;
    printColoredText(colorYellow, text);
}

void printInfoText(const char *text)
{
    short colorBlue = COLOR_BLUE;
    printColoredText(colorBlue, text);
}
