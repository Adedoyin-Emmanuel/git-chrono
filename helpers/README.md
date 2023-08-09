# Colored Text Helper

This module helps to generate colorized text using ANSI color codes to make the CLI tool more attractive.

`How To Use`
Include the helpers file, and bingo, you can now assess predefined colors functions or better still,
add a color code and then your text

```c
#include "helpers.h"

int main(void)
{
    /* Predefined color codes functions */
    printSuccessText("Hello world\n");
    printErrorText("Hello world\n");
    printInfoText("Hello world\n");
    printWarningText("Hello world\n");

    /*Pass color codes and custom message */
    printColoredText(36, "This is a cyan color text");
}

```
