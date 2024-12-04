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

    if(initClientList(&clients))
    {   
        printf("Clients was not able to initialize!");
        return 1;
    }

    printf("%s\n", clients.list[0].clientMapPath);
    printf("%s\n", clients.list[1].clientMapPath);
    printf("%s\n", clients.list[2].clientMapPath);

    int menuChoice = 0;
    int menuPauseMS = 2000;

    while (true)
    {   
        printf("After continue\n");
        menuChoice = runMainMenu();

        switch(menuChoice)
        {
            case 1: 
                UIscanCard(clients);
                Sleep(menuPauseMS);
                printf("Before continue\n");
                continue;

            case 2:
                UIopenDoor();
                Sleep(menuPauseMS);
                continue;

            case 3:
                printAllCards(clients);
                Sleep(menuPauseMS);
                continue;

            case 4:
                UIchangeAccess(clients);
                Sleep(menuPauseMS);
                continue;

            case 5:
                UIcreateNewClient(&clients);
                Sleep(menuPauseMS);
                continue;

            case 6:
                if(UIexitProgram()) break;
                Sleep(menuPauseMS);
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