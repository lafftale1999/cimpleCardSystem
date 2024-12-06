#include "../include/access.h"
#include "../include/doorSystem.h"
#include "../include/interface.h"
#include <math.h>
#include <time.h>

int authorizeClient(Clients clients, int cardId)
{
    Restriction access;

    if(cardId == -1) return -1;

    int clientIndex = findClientId(cardId, clients);

    if(clientIndex != -1) 
        access = checkClientAccess(clients.list[clientIndex]);

    else 
    {
        printf("Card is not in system!\n");
        access = N_ACCESS;
    }

    switch (access)
    {
    case ACCESS:
        openDoor();
        break;
    
    case N_ACCESS:
        printf("You do not have access!\n");
        break;

    default:
        printf("Something went wrong! authorizeClient() access.c\n");
        break;
    }
}

int generateCardId(Clients *clients)
{
    srand(time(NULL));

    int rnd = 0;

    while (1)
    {
        rnd = rand() % 10000;

        for(int i = 0; i < clients->fill; i++)
        {
            if(rnd == clients->list[i].id) continue;
        }

        return rnd;
    }
}