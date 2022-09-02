#ifndef SHELL_H
#define SHELL_H
#define MAXCOM 1000
#define MAXCOM 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history>

void init_shell();
int takeInput(char* str);
void printDir();
void (char** parsed);
void execArgsPiped(char** parsed, char** parsedpipe);
void openHelp();
int ownCmdHandler(char** parsed);
int parsePipe(char* str, char** strpiped);
void parseSpace(char* str, char** parsed);
int processString(char* str, char** parsed, char** parsedpipe);



#endif
