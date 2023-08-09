#ifndef CONTRIBUTION_GRAPH_H
#define CONTRIBUTION_GRAPH_H
#define SATURATION 72
#define WEEK 7
#define COLS 75
#define MAX_COMMITS 10
#define START_DATE ""
#define MAX_PATTERN_SIZE (COLS * WEEK + 1)

#include <time.h>

/*Mapping out necessary functions*/
time_t parseTime(char *value);
const char *formatTime(time_t time);
time_t nextDay(time_t value);
time_t addRandomDuration(time_t value);


void doCommits(time_t date, int maxCommits, int totalCommits);


/*variables*/

int saturation;
int columns;
int maxCommits;
char *startDate;
int totalCommits;

#endif
