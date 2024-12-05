#ifndef INTERFACE_H
#define INTERFACE_H

#include "config.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int runMainMenu();
void printMenuOptions(char *menu[], char menuMessage[], int size);
void printInformation(char *headline, char *message);
void printAllCards(Clients *clients);
void UIopenDoor();
void UIscanCard(Clients clients);
void UIcreateNewClient(Clients *clients);
void UIchangeAccess(Clients clients);
int UIexitProgram();
int UIremoveCard(Clients *clients);
int getCardIndex(Clients *clients);

#endif