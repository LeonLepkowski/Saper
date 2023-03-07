#include "argParser.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct difficulty {
    int maxRows, maxCols;
    int mines;
    char *name;
} difficulty;

#define DIFFICULTY_CNT 4
static difficulty difficulties[DIFFICULTY_CNT] = {
    {9, 9, 10, "--beginner"},
    {16, 16, 40, "--intermediate"},
    {16, 40, 99, "--expert"},
    {0, 0, 0, "--custom"}
};

#define INVALID_ARGC_MSG "Too few arguments, try again!\nUse --help to print help\n"
#define INVALID_ARG_MSG "Invalid argument.\nUse --help to print help\n"

inline bool requireSize(difficulty *gameMode) {
    return gameMode->maxCols == 0 && gameMode->maxRows == 0 && gameMode->mines == 0;
}

bool convertToInt(char* str, int* res) {
    errno = 0;
    char *end;
    int i  = strtol(str, &end, 10);
    if(*end != '\0') return false;
    if(errno == ERANGE) return false;
    *res = i;
    return true;
}

void printHelp(char* programName) {
    printf("Uruchamianie:\n  %s <DIFFICULTY> <OPTIONS>\n\n", programName);
    printf("Difficulties:\n");
    for(int i = 0; i < DIFFICULTY_CNT; i++) {
        printf("  %s", difficulties[i].name);
        if(requireSize(&difficulties[i])) {
            printf(" <ROWS> <COLUMNS> <MINES>");
        }
        putchar('\n');
    }
    printf("\nOptions:\n  --slim\n\n");
}

int isDifficulty(const char* str) {
    for(int i = 0; i < DIFFICULTY_CNT; i++) {
        if(strcmp(difficulties[i].name, str) == 0) {
            return i;
        }
    }
    return -1;
}

bool start(int argc, char* argv[], int* slim, int* MAX_ROWS, int* MAX_COLS, int* MINES) {
    int difficultyIndex = -1;
    if(argc <= 1) {
        printf("Too few arguments, try again!\nUse --help to print help\n");
        return true;
    }
    for(int i = 1; i < argc; i++) {
        int tmp = -1;
        if(strcmp(argv[i], "--slim") == 0) {
            *slim = 1;
        }
        else if(strcmp(argv[i], "--help") == 0) {
            printHelp(argv[0]);
            return true;
        }
        else if((tmp = isDifficulty(argv[i])) != -1) {
            printf("%d\n", tmp);
            if(difficultyIndex != -1) {
                printf("Difficulty is already set!\n");
                return true;
            }
            difficultyIndex = tmp; 
            if(requireSize(&difficulties[difficultyIndex])) {
                if(i + 3 >= argc) {
                    printf("You need to specify board size and mines count for this difficulty\n");
                    return true;
                }
                if((!(convertToInt(argv[i + 1], MAX_ROWS) && convertToInt(argv[i + 2], MAX_COLS) && convertToInt(argv[i + 3], MINES))) == true){
                    printf("Invalid format\n");
                    return true;
                }
                i += 3;
            }
            else {
                difficulty* diff = &difficulties[difficultyIndex];
                *MAX_ROWS = diff->maxRows;
                *MAX_COLS = diff->maxCols;
                *MINES = diff->mines;
            }
        }
        else {
            printf("Invalid argument\nUse --help to print help\n");
            return true; 
        }
    }
    
    if (difficultyIndex == -1) {
        printf("Difficulty not specified\nUse --help to print help\n");
        return true;
    }

    if (*MINES >= *MAX_ROWS * *MAX_COLS) {
        printf("TOO MUCH BOMBS!, TRY VALUE OF MINES LOWER THAN %i...\n", *MAX_ROWS * *MAX_COLS);
        return true;
    }


    return false;
}
