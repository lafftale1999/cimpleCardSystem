#ifndef INTERFACE_H
#define INTERFACE_H

#include "../include/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int runMainMenu();
void printMenu(char *menu[], char menuMessage[], int size);
int writeOpenDoor();
void printAllCards(Clients clients);

#endif