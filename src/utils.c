#include <conio.h>
#include <stdio.h>

#include "../include/utils.h"

int kbhit2()
{
    return _kbhit();
}

int getNextKeyboardAction(){
    if(kbhit2()){
        char ch = getch();
        return ch;
    }
    return 0;
}

void clearScreen()
{
    printf("\e[1;1H\e[2J");
}