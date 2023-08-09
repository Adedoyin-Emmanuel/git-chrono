#include "./core/contributionGraph.c"

typedef struct
{
    char **pattern;
    time_t date;
} PatternAndDate;

PatternAndDate generatePattern(int columns, int saturation, time_t startDate);
void printPattern(char **pattern, int columns);
