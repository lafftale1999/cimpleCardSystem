#ifndef KEYGEN_H
#define KEYGEN_H

#include "config.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int createKey(char keyPath[], char mapPath[], Restriction access);

void createSystemKey();

int generateKeyNumbers(unsigned char keyVector[KEY_ROWS][KEY_COLS]);

void printKey(char systemKey[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1]);

void saveKeyToFile(char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1], char filePath[]);

int readKeyFromFile(char tempKey[], char filePath[]);

#endif