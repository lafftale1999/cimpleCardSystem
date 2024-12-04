#include "include/client.h"
#include "include/config.h"
#include "include/interface.h"
#include "include/access.h"
#include "include/interface.h"

#include <Windows.h>

int main()
{
    Clients clients;
    clients.size = 0;
    clients.fill = 0;

    initClientList(&clients);

    int menuChoice = 0;
    
    while (true)
    {   
        menuChoice = runMainMenu();

        switch(menuChoice)
        {
            case 1: 
                UIscanCard(clients);
                continue;

            case 2:
                UIopenDoor();
                continue;

            case 3:
                printAllCards(clients);
                continue;

            case 4:
                UIchangeAccess(clients);
                continue;

            case 5:
                UIcreateNewClient(&clients);
                continue;

            case 6:
                if(UIexitProgram()) break;

            default:
                printf("Something went wrong. Please try again!\n");
                continue;
        }

        break;
    }
    
    free(clients.list);

    return 0;
}