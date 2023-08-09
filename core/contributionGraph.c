#include <stdlib.h>
#include "./../helpers/helpers.h"
#include "contributionGraph.h"
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

time_t parseTime(char *value)
{
    if (!value)
    {
        throwError("Incomplete arguments, value is missing\n");
    }

    struct tm *timeInfo;

    if (strftime(value, sizeof(value), "%m/%d/%Y", timeInfo) == 0)
    {
        throwError("Please provide a valid date in MM/DD/YYYY format.\n");
        exit(2);
    }

    return mktime(timeInfo);
}

/*Format time into a string*/
const char *formatTime(time_t time)
{
    if (!time)
    {
        throwError("Incomplete arguments, time is missing\n");
    }
    static char formatted[20];
    strftime(formatted, sizeof(formatted), "%Y-%m-%dT%H:%M:%S", localtime(&time));

    return formatted;
}

/*Add a day to the give date*/
time_t nextDay(time_t value)
{
    if (!value)
    {
        throwError("Incomplete arguments, value is missing\n");
    }

    struct tm *timeInfo = localtime(&value);
    timeInfo->tm_mday += 1;

    return mktime(timeInfo);
}

time_t addRandomDuration(time_t value)
{
    if (!value)
    {
        throwError("Incomplete arguments, value is missing\n");
    }

    struct tm *timeInfo = localtime(&value);

    int hours = rand() % 24;
    int minutes = rand() % 60;
    int seconds = rand() % 60;

    timeInfo->tm_hour += hours;
    timeInfo->tm_min += minutes;
    timeInfo->tm_sec += seconds;

    return mktime(timeInfo);
}

void doCommits(time_t date, int maxCommits, int totalCommits)
{
    if (!date || !maxCommits)
    {
        throwError("Incomplete arguments, date is missing\n");
        return;
    }

    bool flag = true;

    struct timeval start, current;
    gettimeofday(&start, NULL);

    struct tm *dateInfo = localtime(&date);

    /* Current Year*/
    int currentYear = dateInfo->tm_year + 1900;

    // Calculate the end date (end of the current year)
    struct tm endDateInfo = *dateInfo;
    endDateInfo.tm_mon = 11; // December
    endDateInfo.tm_mday = 31;
    time_t endDate = mktime(&endDateInfo);

    while (flag)
    {
        // Check if the year has changed, and if so, wrap it up
        dateInfo = localtime(&date);
        gettimeofday(&current, NULL);
        double elapsedTime = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0;

        if (dateInfo->tm_year + 1900 != currentYear || date >= endDate)
        {

            printf("\x1B[1;32mBingo!🚀 %d commits generated in %.6f seconds duration.\x1B[0m\n", totalCommits, elapsedTime);
            printf("What's next 🤔?\n");
            printf("\x1B[1;34mRun git push origin master .\x1B[0m\n");

            exit(0);
        }

        const char *formatted = formatTime(date);

        /* Set ENV variables :)*/
        setenv("GIT_AUTHOR_DATE", formatted, 1);
        setenv("GIT_COMMITTER_DATE", formatted, 1);

        for (int i = 0; i < maxCommits; i++)
        {
            char msg[100];
            snprintf(msg, sizeof(msg), "Commit: %02d (max: %02d) for Date: %s", totalCommits + 1, maxCommits, formatted);
            char cmd[150];
            snprintf(cmd, sizeof(cmd), "git commit --allow-empty -m \"%s\"", msg);

            system(cmd);

            totalCommits++;
        }
        date = addRandomDuration(date);

        dateInfo = localtime(&date);
    }
}
