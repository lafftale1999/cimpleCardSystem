#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

#define MAP_COLS 8
#define MAP_ROWS 256

#define KEY_N_CHAR 7
#define KEY_COLS 8
#define KEY_ROWS 8

#define SYSTEM_PATH "data/system/"

typedef enum
{
    ACCESS,
    N_ACCESS
} Restriction;

typedef enum
{
    SUCCESS,
    FAILED,
} SystemMessage;

#endif