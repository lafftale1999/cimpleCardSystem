#include "../include/keygen.h"
#include "../include/mapgen.h"
#include "../include/decrypt.h"
#include "../include/encrypt.h"

// creating new key
int createKey(char keyPath[], char mapPath[], Restriction access)
{   
    int flag = 0;

    // two by two vector to save the assigned values
    // these values are the decrypted system key values
    unsigned char keyVector[KEY_ROWS][KEY_COLS];

    // two by two vector to save encrypted key values to
    // these will be assigned by using the specified map in mapPath
    char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1];
    for (int i = 0; i < KEY_ROWS; i++)
        key[i][0] = '\0';
    
    switch (access)
    {
    case ACCESS:
        // first decrypting the systemKey using the systemMap
        flag += decryptKey(keyVector, SYSTEM_PATH "system_key.txt", SYSTEM_PATH "system_map.txt");
        break;
    
    case N_ACCESS:
        flag += generateKeyNumbers(keyVector);
        break;
    
    default:
        printf("\nKey has not been created properly. Out of scope for switch | createKey() keygen.c\n");
        return 1;
    }
    
    // then encrypting the key and saving it to file
    flag += encryptKey(key, keyVector, mapPath);
    saveKeyToFile(key, keyPath);

    return flag;
}

void createSystemKey()
{
    // two by two vector to save the assigned values
    // these values are the decrypted system key values
    unsigned char keyVector[KEY_ROWS][KEY_COLS];

    // two by two vector to save encrypted key values to
    // these will be assigned by using the specified map in mapPath
    char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1];
    for (int i = 0; i < KEY_ROWS; i++)
        key[i][0] = '\0';

    generateKeyNumbers(keyVector);

    encryptKey(key, keyVector, SYSTEM_PATH "system_map.txt");
    saveKeyToFile(key, SYSTEM_PATH "system_key.txt");
    printKey(key);
}

int generateKeyNumbers(unsigned char keyVector[KEY_ROWS][KEY_COLS])
{
    srand(time(NULL));

    int rnd = 0;

    for (int r = 0; r < KEY_ROWS; r++)
    {
        for (int c = 0; c < KEY_COLS; c++)
        {
            rnd = rand() % 256;
            keyVector[r][c] = rnd;

            if(keyVector[r][c] < 0 || keyVector[r][c] > 255)
            {
                printf("Number out of scope | keygen.c");
                return 1;
            }
        }
    }

    return 0;
}

// printing the encrypted key
void printKey(char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1])
{
    // ----------- DEBUG ------------
    printf("\nPRINT CRYPTED KEY START\n");
    // ----------- DEBUG ------------

    printf("----------- PRINT ROWS --------\n");
    for (int i = 0; i < KEY_ROWS; i++)
    {
        printf("%s\n", key[i]);
    }

    printf("----------- PRINT ROWS --------\n");

    printf("----------- PRINT ROWS & COLUMNS --------\n");
    for (int r = 0; r < KEY_ROWS; r++)
    {
        printf("%d | ", r);

        for (int c = 0; c < KEY_COLS; c++)
        {
            for (int i = 0; i < 7; i++)
            {
                printf("%c", key[r][c * 7 + i]);
            }
            
            printf("\t | \t");
        }
        printf("\n");
    }

    printf("----------- PRINT ROWS & COLUMNS --------\n");

    // ----------- DEBUG ------------
    printf("\nPRINT CRYPTED KEY END\n");
    // ----------- DEBUG ------------
}

void saveKeyToFile(char key[KEY_ROWS][KEY_COLS * KEY_N_CHAR + 1], char filePath[])
{
    FILE *file = fopen(filePath, "w");

    for (int i = 0; i < KEY_ROWS; i++)
    {
        fprintf(file, "%s", key[i]);
    }

    fclose(file);
}

int readKeyFromFile(char tempKey[], char filePath[])
{   
    FILE *file;

    file = fopen(filePath, "r");

    if (!file)
    {
        printf("%s does not exist | keygen.c\n", filePath);
        return 1;
    }
   
    fgets(tempKey, (KEY_ROWS * KEY_COLS * KEY_N_CHAR + 1), file);

    fclose(file);

    return 0;
}