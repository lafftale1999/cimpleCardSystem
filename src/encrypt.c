#include "../include/encrypt.h"
#include "../include/mapgen.h"

int encryptKey(char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1],
                unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char mapPath[])
{
    // declaring and initalizing our map for
    // encrypting the key
    char map[MAP_ROWS][MAP_COLS];
    getMap(map, mapPath);

    // encrypting the key by concatenating the assigned
    // sequence of characters by the corresponding index in
    // our map
    for (int r = 0; r < KEY_ROWS; r++)
    {
        for (int c = 0; c < KEY_COLS; c++)
        {
            int mapRow = keyVector[r][c];
            strcat(key[r],map[mapRow]);
        }

        if(strlen(key[r]) != KEY_COLS * KEY_N_CHAR)
        {
            printf("Error assigning key values on row %d | encrypt.c\n");
            return 1;
        }
    }

    return 0;

}
