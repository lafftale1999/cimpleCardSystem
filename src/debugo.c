#include "../include/debugo.h"

#include <stdio.h>
#include <unistd.h> // För getcwd

void printCurrentWorkingDirectory() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}