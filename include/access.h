#ifndef ACCESS_H
#define ACCESS_H

#include "config.h"
#include "client.h"

int authorizeClient(Clients clients, int cardId);
int generateCardId(Clients *clients);

#endif