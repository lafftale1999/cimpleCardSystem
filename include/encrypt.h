#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encryptKey(char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR],
                unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char mapPath[]);

#endif