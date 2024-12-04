#ifndef CLIENT_H
#define CLIENT_H

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLIENT_KEY_PATH "data/client/keys/"
#define CLIENT_MAPS_PATH "data/client/maps/"
#define CLIENT_LIST_PATH "data/client/client_list.txt"
#define CLIENT_COUNT_PATH "data/client/count.txt"

#define N_OF_ATTRIBUTES 4
typedef struct
{
    int id;
    char dateOfRegistration[12];
    char clientMapPath[100];
    char clientKeyPath[100];
} Client;

typedef struct
{
    Client *list;
    int size;
    int fill;
} Clients;

int initClientList(Clients *clients);
int createNewClient(Clients *clients);
int readClientCount(int *clientCount);
void increaseClientCount(int clientCount);
int createKeyPath(Client *client);
int createMapPath(Client *client);
int createRegistrationDate(Client *client);
int compareKeyVectors(  unsigned char systemKeyVector[KEY_ROWS][KEY_COLS],
                        unsigned char clientKeyVector[KEY_ROWS][KEY_COLS]);

Restriction checkClientAccess(Client client);
int findClientId(int searchId, Clients clients);

#endif