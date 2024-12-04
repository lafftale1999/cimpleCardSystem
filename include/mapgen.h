#ifndef MAPGEN_H
#define MAPGEN_H

#include "config.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

int getMap(char map[MAP_ROWS][MAP_COLS], char mapPath[]);
int readMapFromFile(char hashString[], char mapPath[]);
int mapHashString(char systemHash[], char systemMap[MAP_ROWS][MAP_COLS]);
int generateMapString(char map[]);
bool isUnique(char tempString[], char map[], int currentSize);
void createSystemMap();
int createClientMap(char mapPath[]);
void saveMapToFile(char map[], char mapPath[]);

#endif