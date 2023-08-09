#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    const char *option;
    int *value;

} OptionWithValue;

int parseCommandLineArguments(int argc, char *argv[], const OptionWithValue *options, int numOptions);

int parseCommandLineArguments(int argc, char *argv[], const OptionWithValue *options, int numOptions)
{
    if (argc < 2)
        return (EXIT_SUCCESS);

    for (int i = 0; i < argc; i++)
    {
        for (int j = 0; j < numOptions; j++)
        {
            if (strcmp(argv[i], options[j].option) == 0)
            {
                if (strcmp(options[j].option, "-h") == 0 || strcmp(options[j].option, "--help") == 0)
                {
                    /* Print help information*/
                    printf("Help information:\n");
                    printf("Usage: %s [options]\n", argv[0]);
                    printf("Options:\n");
                    for (int k = 0; k < numOptions; k++)
                    {
                        printf("  %s\n", options[k].option);
                    }
                    exit(EXIT_SUCCESS);
                }

                if (1 + i < argc)
                {
                    *(options[j].value) = atoi(argv[i + 1]);
                }
            }
        }
    }

    return (EXIT_FAILURE);
}
