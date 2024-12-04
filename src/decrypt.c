#include "../include/decrypt.h"
#include "../include/keygen.h"
#include "../include/mapgen.h"

int decryptKey( unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char keyPath[], char mapPath[])
{
    int flag = 0;

    char map[MAP_ROWS][MAP_COLS];

    // key is used to store the encrypted system value in
    char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1];
    
    // tempKey is used to store the unformatted keystring from file in
    char tempKey[(KEY_ROWS * KEY_COLS * KEY_N_CHAR + 1)];
    tempKey[0] = '\0';
    
    flag += getMap(map, mapPath); // works
    flag += readKeyFromFile(tempKey, keyPath); // works
    flag += structureKey(key, tempKey); // works
    flag += solveKey(map, keyVector, key);

    return flag;
}

int structureKey(   char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1],
                    char tempKey[KEY_ROWS * KEY_COLS * KEY_N_CHAR + 1])
{
    int index = 0;

    for (int r = 0; r < KEY_ROWS; r++)
    {
        for (int c = 0; c < KEY_COLS; c++)
        {
            for (int i = 0; i < KEY_N_CHAR; i++)
            {
                key[r][c * KEY_N_CHAR + i] = tempKey[index++];
            }
        }

        key[r][KEY_COLS * KEY_N_CHAR] = '\0';

        if(strlen(key[r]) != KEY_COLS * KEY_N_CHAR)
        {
            printf("Error structuring key at row %d | decrypt.c\n", r);
            printf("%s | %d\n", key[r], strlen(key[r]));
            printf("Length should be: %d", KEY_COLS * KEY_N_CHAR);
            return 1;
        }
    }

    return 0;
}

int solveKey(  char systemMap[MAP_ROWS][MAP_COLS],
                unsigned char keyVector[KEY_ROWS][KEY_COLS],
                char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1])
{
    for (int r = 0; r < KEY_ROWS; r++)
    {
        for (int c = 0; c < KEY_COLS; c++)
        {
            char temp[KEY_N_CHAR + 1];
            generateString(temp, key, r, c);

            decryptValues(systemMap, keyVector, temp, r, c);
            
            if (!(keyVector[r][c] >= 0 && keyVector[r][c] <= 255))
            {
                printf("Error decrypting values at keyVector[%d][%d] | decrypt.c\n", r, c);
                return 1;
            }
        }
    }

    return 0;
}

void generateString(char temp[KEY_N_CHAR + 1],
                    char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1],
                    int r, int c)
{   
    for (int i = 0; i < KEY_N_CHAR + 1; i++)
    {
        if (i < 7)
        {
            temp[i] = key[r][c * (KEY_N_CHAR) + i];
            continue;
        }
    }

    temp[KEY_N_CHAR] = '\0';
}

void decryptValues( char systemMap[MAP_ROWS][MAP_COLS],
                    unsigned char keyVector[KEY_ROWS][KEY_COLS],
                    char temp[], int r, int c)
{
    int index = 0;

    while(index <= 255)
    {   
        // compare strings
        if (!strcmp(systemMap[index], temp))
        {
            keyVector[r][c] = index;
            break;
        }
        
        index++;
    }
}

// printing the encrypted key
void printDecryptedKey(unsigned char keyVector[KEY_ROWS][KEY_COLS])
{
    for (int r = 0; r < KEY_ROWS; r++)
    {
        printf("%d | ", r);
        for (int c = 0; c < KEY_COLS; c++)
        {
            printf("%d", keyVector[r][c]);
        
            printf("\t | \t");
        }
        printf("\n");
    }
}