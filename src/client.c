#include "../include/client.h"
#include "../include/keygen.h"
#include "../include/mapgen.h"
#include "../include/decrypt.h"
#include "../include/safeinput.h"
#include "../include/access.h"

int initClientList(Clients *clients)
{
    if(countClientsInListFile(clients) == -1) return -1;
    clients->size = clients->fill + 10;

    if(clientMalloc(clients) == -1) return -1;
    if(readClientListFromFile(clients) == -1) return -1;
    
    return 0;
}

int createNewClient(Clients *clients)
{
    if(checkClientRealloc(clients) == -1) return - 1;

    int flag = 0;

    clients->list[clients->fill].id = generateCardId(clients);

    Restriction access = giveAccess();
    
    flag += createKeyPath(&clients->list[clients->fill]);
    flag += createMapPath(&clients->list[clients->fill]);
    flag += createRegistrationDate(&clients->list[clients->fill]);

    flag += createClientMap(clients->list[clients->fill].clientMapPath);
    flag += createKey(
        clients->list[clients->fill].clientKeyPath,
        clients->list[clients->fill].clientMapPath,
        access);

    if(flag){
        printf("Client creation failed. Read log | createNewClient() client.c\n");
        return -1;
    }

    clients->fill++;
    writeClientListToFile(*clients, clients->fill);

    return 0;
}

Restriction giveAccess()
{
    printf("Which type of access should the client have?\n");
    printf("Enter (1) for access or (2) for no access!\n");

    int userInput;
    bool inputResult;

    while(true)
    {
        inputResult = GetInputInt("> ", &userInput);

        if(inputResult)
        {
            if(userInput == 1) return ACCESS;

            else if(userInput == 2) return N_ACCESS;

            printf("Please enter either (1) for access or (2) for no access!\n");
            continue;

        }

        else 
        {
            printf("Input too long: Please enter either (1) for access or (2) for no access!");
            continue;
        }

        printf("Something went wrong! | giveAccess() client.c");
    }
}

int createKeyPath(Client *client)
{
    char keyPath[50];
    sprintf(keyPath, "%s%d.txt", CLIENT_KEY_PATH, client->id);

    client->clientKeyPath[0] = '\0';
    strcat(client->clientKeyPath, keyPath);

    if (client->clientKeyPath[0] == '\0')
    {
        printf("Error creating keyPath for client | createKeyPath() client.c\n");
        return 1;
    }

    return 0;
}

int createMapPath(Client *client)
{
    char mapPath[50];
    sprintf(mapPath, "%s%d.txt", CLIENT_MAPS_PATH, client->id);

    client->clientMapPath[0] = '\0';
    strcat(client->clientMapPath, mapPath);

    if (client->clientMapPath[0] == '\0')
    {
        printf("Error creating mapPath for client | createMapPath() client.c\n");
        return 1;
    }

    return 0;
}

int createRegistrationDate(Client *client)
{
    time_t t;
    time(&t);

    sprintf(client->dateOfRegistration, "%s", ctime(&t));

    client->dateOfRegistration[strlen(client->dateOfRegistration) - 1] = '\0';
    
    if(client->dateOfRegistration[0] == '\0')
    {
        printf("Error creating date for client| createRegistrationDate() client.c\n");
        return 1;
    }

    return 0;
}

int compareKeyVectors(  unsigned char systemKeyVector[KEY_ROWS][KEY_COLS],
                        unsigned char clientKeyVector[KEY_ROWS][KEY_COLS])
{
    for (int r = 0; r < KEY_ROWS; r++)
    {
        for (int c = 0; c < KEY_COLS; c++)
        {
            if(!(systemKeyVector[r][c] == clientKeyVector[r][c]))
            {
                return 1;
            }
        }
    }

    return 0;
}

Restriction checkClientAccess(Client client)
{
    int flag = 0;

    // decrypt client
    unsigned char clientKeyVector[KEY_ROWS][KEY_COLS];
    flag += decryptKey(clientKeyVector, client.clientKeyPath, client.clientMapPath);

    // decrypt system
    unsigned char systemKeyVector[KEY_ROWS][KEY_COLS];
    flag += decryptKey(systemKeyVector, SYSTEM_PATH "system_key.txt", SYSTEM_PATH "system_map.txt");

    if (flag)
    {
        printf("Checking access was unsuccessful. Read logs | checkClientAccess() client.c\n");
        
        return N_ACCESS;
    }

    if(!compareKeyVectors(systemKeyVector, clientKeyVector))
    {
        return ACCESS;
    }
    
    return N_ACCESS;
}

int findClientId(int searchId, Clients clients)
{   
    int size = clients.fill;

    int s = 0;
    int e = size - 1;
    int i = 0;

    // check that client id is within scope
    if(searchId < clients.list[s].id && searchId > clients.list[e].id)
    {
        return -1;
    }

    while(size > 2)
    {
        i = e - (size/2);

        // client id found
        if(clients.list[i].id == searchId) return i;

        // client id smaller
        else if (clients.list[i].id < searchId) e = i;

        // client id bigger
        else if (clients.list[i].id > searchId) s = i;

        // client not found
        else return -1;
    }

    // see if the last two is the client id
    if (clients.list[s].id == searchId) return s;
    else if (clients.list[e].id == searchId) return e;

    // if not return -1
    return -1;
}

int countClientsInListFile(Clients *clients)
{
    FILE *file = fopen(CLIENT_LIST_PATH, "r");

    if(!file)
    {
        printf("%s didnt exist! | countClients() client.c\n", CLIENT_LIST_PATH);
        return -1;
    }

    char ch;
    int commaCounter = 0;

    while((ch = fgetc(file)) != EOF)
    {
        if(ch == ',') 
        {
            commaCounter++;
        }
    }

    fclose(file);

    clients->fill = commaCounter / N_OF_ATTRIBUTES;

    return 0;
}

int writeClientListToFile(Clients clients, int listSize)
{
    FILE *file = fopen(CLIENT_LIST_PATH, "w");

    char tempString[255];
    tempString[0] = '\0';

    for (int i = 0; i < listSize; i++)
    {
        fprintf(file, 
            "%d,%s,%s,%s,",
            clients.list[i].id, 
            clients.list[i].dateOfRegistration, 
            clients.list[i].clientMapPath, 
            clients.list[i].clientKeyPath
            );
    }

    fclose(file);
}

int readClientListFromFile(Clients *clients)
{
    FILE *file = fopen(CLIENT_LIST_PATH, "r");

    if (!file)
    {
        printf("%s didn't exist! | readClientList() client.c\n", CLIENT_LIST_PATH);
        return -1;
    }

    char ch;
    int index = 0;
    int attribute = 0;

    char tempString[255];
    int tempIndex = 0;

    while ((ch = fgetc(file)) != '\n' && ch != EOF)
    {

        if (attribute < 4)
        {

            if(ch != ',')
            {
                tempString[tempIndex++] = ch;
                continue;
            }

            tempString[tempIndex] = '\0';
            tempIndex = 0;

            switch(attribute)
            {
                case 0:
                    clients->list[index].id = atoi(tempString);
                    break;

                case 1:
                    strcpy(clients->list[index].dateOfRegistration, tempString);
                    break;

                case 2:
                    strcpy(clients->list[index].clientMapPath, tempString);
                    break;

                case 3:
                    strcpy(clients->list[index].clientKeyPath, tempString);
                    break;
            }
        attribute++;
        continue;
        }

        tempString[tempIndex++] = ch;
        index++;
        attribute = 0;
    }

    return 0;
}

int clientMalloc(Clients *clients)
{
    clients->list = (Client*)malloc(clients->size * sizeof(Client));

    if (!clients->list)
    {
        printf("Memory allocation failed | clientMalloc() client.c\n");
        return -1;
    }

    return 0;
}

int checkClientRealloc(Clients *clients)
{
    if (clients->fill == clients->size)
    {
        Client *pTemp;

        clients->size += 10;

        pTemp = (Client*)realloc(clients->list, clients->size * sizeof(Client));

        if (!pTemp)
        {
            printf("Reallocation failed. | checkClientRealloc() client.c\n");
            return -1;
        }

        clients->list = pTemp;
    }

    return 0;
}

int changeAccess(Client client, Restriction access)
{
    createKey(client.clientKeyPath, client.clientMapPath, access);
}