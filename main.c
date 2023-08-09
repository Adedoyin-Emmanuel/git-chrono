#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[])
{
    /*parse command line arguments and stuff*/

    int defaultSaturation = SATURATION, defaultColumns = COLS, defaultMaxCommits = MAX_COMMITS;
    char *defaultDate = NULL;
    int backupDate = -1;
    char satStr[20], dateStr[20], colStr[20], maxCommitsStr[20], backupDateStr[20];

    OptionWithValue options[] = {
        {"-s", &defaultSaturation},
        {"--saturation", &defaultSaturation},
        {"-c", &defaultColumns},
        {"--columns", &defaultColumns},
        {"-m", &defaultMaxCommits},
        {"--max-commits", &defaultMaxCommits},
        {"-h", NULL},
        {"--help", NULL}

    };

    int numOptions = sizeof(options) / sizeof(options[0]);

    if (parseCommandLineArguments(argc, argv, options, numOptions))
    {
        printf("Saturation: %d\n", defaultSaturation);
        printf("Columns: %d\n", defaultColumns);
        printf("Max-Commits: %d\n", defaultMaxCommits);

        printf("\x1B[1;32mPlotting Your Awesome Contribution Graph😋\x1B[0m\n");
        
        if (defaultSaturation > 1 || defaultSaturation > 100)
        {
            defaultSaturation = SATURATION;
        }

        saturation = defaultSaturation;
        columns = defaultColumns;
        maxCommits = defaultMaxCommits;
        totalCommits = 0;
        time_t date;

        if (backupDate == -1)
        {
            time_t currentTime = time(NULL);
            struct tm *localDateInfo = localtime(&currentTime);

            /* Set the date to the beginning of the current year */
            localDateInfo->tm_mday = 1;
            localDateInfo->tm_mon = 0;
            localDateInfo->tm_hour = 0;
            localDateInfo->tm_min = 0;
            localDateInfo->tm_sec = 0;

            time_t startDate = mktime(localDateInfo);

            date = startDate;
        }

        PatternAndDate patternAndDate = generatePattern(columns, saturation, date);

        char **pattern = patternAndDate.pattern;
        //This bug gave me headache 🤯 date = patternAndDate.date;

        /* Generate commits based on the pattern, the pattern maps to working days of the week */
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < WEEK; j++)
            {
                if (pattern[i][j] == '0')
                {
                    doCommits(date, maxCommits, totalCommits);
                }
                date = nextDay(date);
            }
        }

        // Free memory allocated for the pattern
        for (int i = 0; i < columns; i++)
        {
            free(pattern[i]);
        }
        free(pattern);
    }
    else
    {
        printWarningText("Options not provided");
    }

    return 0;
}

PatternAndDate generatePattern(int columns, int saturation, time_t startDate)
{
    PatternAndDate patternAndDate;
    patternAndDate.pattern = malloc(columns * sizeof(char *));
    patternAndDate.date = startDate;

    for (int i = 0; i < columns; i++)
    {
        patternAndDate.pattern[i] = malloc((WEEK + 1) * sizeof(char)); /* +1 for null terminator */
        patternAndDate.pattern[i][WEEK] = '\0';                        /* Null-terminate each row */

        for (int j = 0; j < WEEK; j++)
        {
            if (rand() % 100 > saturation)
            {
                patternAndDate.pattern[i][j] = '.';
            }
            else
            {
                patternAndDate.pattern[i][j] = '0';
            }
        }

        /* Update the date for the next column */
        patternAndDate.date = nextDay(patternAndDate.date);
    }

    return patternAndDate;
}

void printPattern(char **pattern, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        printf("%s\n", pattern[i]);
        free(pattern[i]);
    }
    free(pattern);
}
