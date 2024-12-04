#include "../include/interface.h"
#include "../include/utils.h"
#include "../include/safeinput.h"
#include "../include/client.h"
#include "../include/doorSystem.h"
#include "../include/access.h"

#include <ctype.h>

#define MENU_OPTIONS 6

int runMainMenu()
{
    char *menuOptions[] = {
        "SCAN CARD",
        "FORCE OPEN DOOR",
        "SHOW CARDS",
        "CHANGE ACCESS",
        "ADD NEW CARD"
        "EXIT PROGRAM"};

    
    printMenu(menuOptions, "CARDSYSTEM 1.0.0 - YOUR SAFETY IS OUR MONEY", MENU_OPTIONS);

    int userChoice;
    INPUT_RESULT inputResult;

    while (true)
    {
        inputResult = GetInputInt("> ", &userChoice);

        switch(inputResult)
        {
            case INPUT_RESULT_OK:
                if(userChoice < 1 || userChoice > MENU_OPTIONS)
                {
                    printf("Enter a number between 1 and %d\n", MENU_OPTIONS);
                    continue;
                }
                return userChoice;

            case INPUT_RESULT_NO_INPUT:
                printf("You have to enter something\n");
                continue;

            case INPUT_RESULT_TOO_LONG:
                printf("Number entered is too big. Please enter a number between 1 and %d!\n", MENU_OPTIONS);
                continue;

            default:
                printf("Something went wrong! runMainMenu() interface.c\n");
                continue;
        }   
    }
}

void printMenu(char *menu[], char menuMessage[], int size)
{
    clearScreen();
    
    printf("%s\n", menuMessage);

    for (int i = 0; i < size; i++)
    {
        printf("%d. %s\n", i + 1, menu[i]);
    }
}

void UIopenDoor()
{
    openDoor();
}

void printAllCards(Clients clients)
{
    printMenu("Listing all cards", "LIST ALL CARDS", 1);

    if (clients.size > 0)
    {
        for (int i = 0; i < clients.size; i++)
        {
            printf("%d | %s | %s",
            clients.list[i].id,
            checkClientAccess(clients.list[i]) == ACCESS ? "Access" : "No Access",
            clients.list[i].dateOfRegistration);
        }
    }
}

void UIscanCard(Clients clients)
{
    printMenu("Enter the card to be scanned ('x' to go back):", "SCAN CARD", 1);

    int clientId = scanCard();

    authorizeClient(clients, clientId);
    sleep(2);
}

void UIcreateNewClient(Clients *clients)
{   
    printMenu("Creating new client...", "CREATE NEW CLIENT", 1);

    if(!createNewClient(&clients))
    {   
        printMenu("Creating new client...", "CREATE NEW CLIENT", 1);
        printf("Client created!\n");
        printf("Client Id: %d\n", clients->list[clients->fill - 1].id);
        printf("Access: %s\n", checkClientAccess(clients->list[clients->fill - 1]) == ACCESS ? "ACCESS" : "NO ACCESS");
        printf("Date: %s\n", clients->list[clients->fill - 1].dateOfRegistration);
    }

    else
    {
        printf("Client creation failed! | UIcreateNewClient() interface.c\n");
    }

    sleep(2);
}

void UIchangeAccess(Clients clients)
{
    printMenu("Enter card to be scanned or (x) to go back!", "CHANGE ACCESS", 1);

    int clientID = scanCard();
    int listIndex = findClientId(clientID, clients);

    if (listIndex != -1)
    {
        Restriction access = giveAccess();

        changeAccess(clients.list[listIndex], access);
    }

    else
    {
        printf("Card Id does not exist!\n");
    }

    sleep(2);
}

void UIexitProgram()
{
    printMenu("Are you sure you wanna exit the program?", "EXIT PROGRAM", 1);

    printf("Enter (y) for yes or (n) for no\n");

    char input;

    while (1)
    {
        GetInputChar("> ", &input);

        if (tolower(input) == 'y')
        {
            printf("Exiting program...\n");
            return -1;
        }

        else if (tolower(input) == 'n')
        {
            printf("Going back to main menu...\n");
            return 0;
        }

        else
        {
            printf("Enter either (y) for yes or (n) for no");
        }
    }
}