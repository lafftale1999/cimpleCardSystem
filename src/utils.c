#include <conio.h>
#include <stdio.h>
#include <windows.h>

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

int removeFile(char filePath[])
{
    if(remove(filePath) == 0)
    {
        printf("%s was successfully removed\n", filePath);
        return 0;
    }

    Sleep(100);
    
    printf("There was an error removing file: %s", filePath);
    return 1;
}