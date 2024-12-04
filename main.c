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
    
    int menuPause = 2000;
    while (true)
    {   
        menuChoice = runMainMenu();

        switch(menuChoice)
        {
            case 1: 
                UIscanCard(clients);
                Sleep(menuPause);
                continue;

            case 2:
                UIopenDoor();
                Sleep(menuPause);
                continue;

            case 3:
                printAllCards(clients);
                Sleep(menuPause);
                continue;

            case 4:
                UIchangeAccess(clients);
                Sleep(menuPause);
                continue;

            case 5:
                UIcreateNewClient(&clients);
                Sleep(menuPause);
                continue;

            case 6:
                if(UIexitProgram()) break;
                Sleep(menuPause);
                continue;

            default:
                printf("Something went wrong. Please try again!\n");
                Sleep(menuPause);
                continue;
        }

        break;
    }
    
    free(clients.list);

    return 0;
}