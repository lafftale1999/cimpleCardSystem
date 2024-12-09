#include "include/client.h"
#include "include/config.h"
#include "include/interface.h"
#include "include/access.h"
#include "include/interface.h"
#include "include/utils.h"

#include <Windows.h>

int main()
{
    Clients clients;
    clients.size = 0;
    clients.fill = 0;

    if(initClientList(&clients))
    {   
        printf("Clients was not able to initialize!");
        return 1;
    }

    int menuChoice = 0;
    const int menuPauseMS = 2000;

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
                UIprintCards(&clients);
                continue;

            case 4:
                UIchangeAccess(clients);
                continue;

            case 5:
                UIcreateNewClient(&clients);
                continue;

            case 6:
                UIremoveCard(&clients);
                continue;

            case 7:
                if(UIexitProgram()) break;
                continue;

            default:
                printf("Something went wrong. Please try again!\n");
                Sleep(menuPauseMS);
                continue;
        }

        break;
    }
    
    free(clients.list);

    return 0;
}
