#include "../include/access.h"
#include "../include/doorSystem.h"
#include "../include/interface.h"

int authorizeClient(Clients clients, int cardId)
{
    Restriction access;

    if(cardId == -1) return -1;

    int clientIndex = findClientId(cardId, clients);

    if(clientIndex != -1) 
        access = checkClientAccess(clients.list[clientIndex]);

    else access = N_ACCESS;

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