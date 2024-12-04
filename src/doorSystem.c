#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/doorSystem.h"
#include "../include/interface.h"
#include "../include/client.h"
#include "../include/safeinput.h"

int scanCard()
{   
    #define BUFFER_SIZE 8
    char userInput[BUFFER_SIZE];

    int cardId;
    char *endPointer;
    INPUT_RESULT inputResult;

    while(true)
    {
        inputResult = GetInput("> ", userInput, BUFFER_SIZE);
        
        switch (inputResult)
        {
        case INPUT_RESULT_OK:
            // check if user want to go back
            if (tolower(userInput[0]) == 'x' && userInput[1] == '\0') return -1;

            cardId = strtol(userInput, &endPointer, 10);

            if (endPointer == userInput)
            {
                printf("Please enter a number or 'x' to go back\n");
                continue;
            }

            else if (cardId < 0)
            {
                printf("Please enter a positive number!\n");
                continue;
            }

            return cardId;
        
        case INPUT_RESULT_TOO_LONG:
            printf("The number is too big, try again!\n");
            continue;

        case INPUT_RESULT_NO_INPUT:
            printf("You have to enter something!\n");
            continue;
        
        default:
            printf("Something went wrong! scanCard() doorSystem.c\n");
            continue;
        }
    }
}

int openDoor()
{
    for (int i = 0; i < 10; i++)
    {
        if(i != 5)
        {
            printf("\n");
            continue;
        }

        printf("---------- DOOR IS NOW OPEN! ------------\n");
    }
}