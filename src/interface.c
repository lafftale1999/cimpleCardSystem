#include "../include/interface.h"
#include "../include/utils.h"
#include "../include/safeinput.h"
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

    
    printMenuOptions(menuOptions, "CARDSYSTEM 1.0.0 - YOUR SAFETY IS OUR MONEY", MENU_OPTIONS);

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

void printMenuOptions(char *menu[], char menuMessage[], int size)
{
    clearScreen();
    
    printf("%s\n", menuMessage);

    for (int i = 0; i < size; i++)
    {
        printf("%d. %s\n", i + 1, menu[i]);
    }
}

void printInformation(char *headline, char *message)
{
    clearScreen();

    printf("%s\n", *headline);
    printf("%s\n", *message);
}

void printAllCards(Clients clients)
{
    printInformation("LIST ALL CARDS", "Listing all cards");

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

void UIopenDoor()
{
    clearScreen();
    openDoor();
}

void UIscanCard(Clients clients)
{   
    printInformation("SCAN CARD", "Enter the card to be scanned ('x' to go back):");

    int cardId = scanCard();

    authorizeClient(clients, cardId);
}

void UIcreateNewClient(Clients *clients)
{   
    printInformation("CREATE NEW CLIENT", "Creating new client...");

    if(!createNewClient(clients))
    {   
        printf("Client created!\n");
        printf("Client Id: %d\n", clients->list[clients->fill - 1].id);
        printf("Access: %s\n", checkClientAccess(clients->list[clients->fill - 1]) == ACCESS ? "ACCESS" : "NO ACCESS");
        printf("Date: %s\n", clients->list[clients->fill - 1].dateOfRegistration);
    }

    else
    {
        printf("Client creation failed! | UIcreateNewClient() interface.c\n");
    }
}

void UIchangeAccess(Clients clients)
{
    printInformation("CHANGE ACCESS", "Enter card to be scanned or (x) to go back!");

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
}

int UIexitProgram()
{   
    printInformation("EXIT PROGRAM", "Are you sure you wanna exit the program?");

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