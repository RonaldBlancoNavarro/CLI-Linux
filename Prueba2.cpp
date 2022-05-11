#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include "readline/readline.h"
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#define MAXCOM 1000
#define MAXLIST 100
#define clear() cout << "\033[H\033[j";

using namespace std;

void inicio()
{
    clear();
    cout << "\n\n\n\n******************"
            "************************";
    cout << "\n\n\n\t****MY SHELL****";
    cout << "\n\n\t-USE AT YOUR OWN RISK-";
    cout << "\n\n\n\n*******************"
            "***********************";
    char *username = getenv("USER");
    cout << "\n\n\nUSER is: @%s" << username;
    cout << "\n";
    sleep(1);
    clear();
}

int takeInput(char *str)
{
    char *buf;

    buf = readline("\n>>> ");
    if (strlen(buf) != 0)
    {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    }
    else
    {
        return 1;
    }
    
}

void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

void execArgs(char **parsed)
{
    // Forking a child
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
    }
    else
    {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}

void execArgsPiped(char **parsed, char **parsedpipe)
{
    // 0 is read end, 1 is write end
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
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(parsed[0], parsed) < 0)
        {
            printf("\nCould not execute command 1..");
            exit(0);
        }
    }
    else
    {
        // Parent executing
        p2 = fork();

        if (p2 < 0)
        {
            printf("\nCould not fork");
            return;
        }

        // Child 2 executing..
        // It only needs to read at the read end
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
        }
        else
        {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
        }
    }
}

// Help command builtin
void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
         "\nCopyright @ Suprotik Dey"
         "\n-Use the shell at your own risk..."
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");

    return;
}

int ownCmdHandler(char **parsed) //
{
    // int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    // char *ListOfOwnCmds;
    // ListOfOwnCmds = new char[NoOfOwnCmds];
    // char *username;
    // ListOfOwnCmds[0] = "exit";
    // ListOfOwnCmds[1] = "cd";
    // ListOfOwnCmds[2] = "help";
    // ListOfOwnCmds[3] = "hello";


    // for (i = 0; i < NoOfOwnCmds; i++)
    // {
    //     if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0)
    //     {
    //         switchOwnArg = i + 1;
    //         break;
    //     }
    // }

    // switch (switchOwnArg)
    // {
    // case 1:
    //     printf("\nGoodbye\n");
    //     exit(0);
    // case 2:
    //     chdir(parsed[1]);
    //     return 1;
    // case 3:
    //     openHelp();
    //     return 1;
    // case 4:
    //     username = getenv("USER");
    //     printf("\nHello %s.\nMind that this is "
    //            "not a place to play around."
    //            "\nUse help to know more..\n",
    //            username);
    //     return 1;
    // default:
    //     break;
    // }

    return 0;
}

int main()
{
    cout << "Hello World!\n";
    inicio();
    system("pause");
    return 0;
}
