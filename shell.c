#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline.history.h>
#include "shell.h"
/**
 * Clearing the shell using escape sequences
 * Greeting shell during startup
 */
#define MAXCOM 1000
#define MAXLIST 100

#define clear() printf("\033[H\033[J")

void init_shell()
{
	clear();
	printf("\n\n\n\n******************"
			"************************");
	 printf("\n\n\n\t****MY SHELL****");
	 printf("\n\n\t-USE AT YOUR OWN RISK-");
	 printf("\n\n\n\n******************"
			 "************************");
	 char* username = getenv("USER");
	 printf("\n\n\nUSER is: @%s", username);
	 printf("\n");
	 sleep(1);
	 clear();
}
/**
 * Function to take input
 * Function to print Current Directory
 * Function where the system command is executed
 */
int takeInput(char* str)
{
	char* buf;

	buf = readline("\n>>> ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
	{
		return (1);
	}
}
void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

void execArgs(char** parsed)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
		else
		{
			wait(NULL);
			return;
/**
 * Function where the piped system commands is executed
 *
 */
void execArgsPiped(char** parsed, char** parsedpipe)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return;
	}
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
		else
		{
			p2 = fork();

			if (p2 < 0)
			{
				printf("\nCould not fork");
				return;
			}
			if (p2 == 0)
			{
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);

				if (execvp(parsedpipe[0], parsedpipe) < 0)
				{
					printf("\nCould not execute command 2..");
					exit(0);
				}
				else
				{
					wait(NULL);
					wait(NULL);
				}
			}
/**
 * Help command builtin
 * Function to execute builtin commands
 * function for finding pipe
 * function for parsing command words
 */
