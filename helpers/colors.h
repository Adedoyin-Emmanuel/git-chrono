#define COLOR_GREEN 32;
#define COLOR_RED 31;
#define COLOR_YELLOW 33;
#define COLOR_BLUE 34;

/*
    The colors map out to
    Green => Success
    Red => Error
    Yellow => Warning
    Blue => Info

    You get the vibe 🚀
*/

void printColoredText(int colorCode, const char *text);
void printSuccessText(const char *text);
void printErrorText(const char *text);
void printWarningText(const char *text);
void printInfoText(const char *text);

