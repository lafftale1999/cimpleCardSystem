#ifndef DECRYPT_H
#define DECRYPT_H

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decryptKey( unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char keyPath[], char mapPath[]);

int structureKey(  char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1],
                    char tempKey[KEY_ROWS * KEY_COLS * KEY_N_CHAR + 1]);

int solveKey(  char systemMap[MAP_ROWS][MAP_COLS],
                unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1]);

void generateString(char temp[KEY_N_CHAR + 1],
                    char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1],
                    int r, int c);

void decryptValues( char systemMap[MAP_ROWS][MAP_COLS],
                    unsigned char keyVector[KEY_ROWS][KEY_COLS],
                    char temp[], int r, int c);

void printDecryptedKey(unsigned char keyVector[KEY_ROWS][KEY_COLS]);

#endif