#include "../include/mapgen.h"
#include "../include/debugo.h"

// maps our clients map and adds the values to map[][]
int getMap(char map[MAP_ROWS][MAP_COLS], char mapPath[])
{   
    // keeps track if anything went wrong
    int flags = 0;
    
    // declares string and iniates null to avoid scrap
    char hashString[MAP_COLS * MAP_ROWS + 1];
    hashString[0] = '\0';

    // reads the hashed string from file
    flags += readMapFromFile(hashString, mapPath);

    // maps it
    flags += mapHashString(hashString, map);

    return flags;
}

int readMapFromFile(char hashString[], char mapPath[])
{   
    FILE *file = fopen(mapPath, "r");

    if (file == NULL)
    {
        printf("%s | File does not exist | mapgen.c\n", mapPath);
        return 1;
    }

    fgets(hashString, (MAP_COLS * MAP_ROWS + 1), file);
    
    fclose(file);
    
    return 0;
}

// Mapping the hashed string
int mapHashString(char hashString[], char map[MAP_ROWS][MAP_COLS])
{   
    // checking if the string contains letters
    if (strlen(hashString) > 1)
    {
        // logic for decrypting string
        for(int r = 0; r < MAP_ROWS; r++)
        {
            for(int c = 0; c < MAP_COLS; c++)
            {
                if(c < MAP_COLS - 1)
                {
                    // mapping a sequence of 7 characters to one value "r"
                    map[r][c] = hashString[r*7 + c];
                    continue;
                }
                map[r][c] = '\0';
            }
        }
    }

    // if not return error value
    else return 1;

    for (int r = 0; r < MAP_ROWS; r++)
    {
        if(strlen(map[r]) != MAP_COLS - 1)
        {
            printf("String not correctly mapped at %d. mapgen.c\n", r);
            return 1;
        }
    }

    return 0;
}

int generateMapString(char map[])
{
    // initializing which characters the system can use
    char *approvedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYabcdefghijklmnopqrstuwvxy!#?_-123456789<>/=";
    int index = strlen(approvedCharacters) - 1;

    // keeping track on how many strings have been added
    int currentSize = 0;

    // randstuff
    srand(time(NULL));
    int rnd = 0;

    char tempString[MAP_COLS];

    // creates an 7 char long string + '\0'
    // and the checks if it's unique
    // if it's not unique we go another round by decrementing i
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            if(j < MAP_COLS - 1)
            {
                rnd = rand() % index;
                tempString[j] = approvedCharacters[rnd];
                continue;
            }

            tempString[j] = '\0';
        }

        if(isUnique(tempString, map, currentSize))
        {
            strcat(map, tempString);
            // printf("%d = %s | unique\n", i, tempString);
            currentSize++;
        }

        else
            i--;
    }

    if (strlen(map) != 1792)
    {
        printf("Map has not been generated correctly. mapgen.c\n");
        return 1;
    }

    return 0;
}

bool isUnique(char tempString[], char map[], int currentSize)
{
    // compares our tempString with a sequence of 7 chars
    for (int r = 0; r < currentSize; r++)
    {
        int index = r * 7;

        if (!strncmp(tempString, &map[index], 7))
            return false;
    }

    return true;
}

// only used to generate new map for system
void createSystemMap()
{
    char systemMap[MAP_ROWS * MAP_COLS];
    systemMap[0] = '\0';

    generateMapString(systemMap);
    saveMapToFile(systemMap, "system/system_map.txt");
}

int createClientMap(char mapPath[])
{   
    int success = 0;
    
    char clientMap[MAP_ROWS * MAP_COLS];

    // scrap-proofing string
    clientMap[0] = '\0';

    success += generateMapString(clientMap);
    saveMapToFile(clientMap, mapPath);

    if (success)
    {
        printf("Error creating client map. mapgen.c\n");
        return 1;
    }

    return 0;
}

void saveMapToFile(char map[], char mapPath[])
{
    FILE *file = fopen(mapPath, "w");

    if (file == NULL)
    {
        printf("Error creating file: %s", mapPath);
        return;
    }

    fprintf(file, "%s", map);

    fclose(file);
}