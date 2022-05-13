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
    system("clear");
    cout << "\n\n******************************************";
    cout << "\n\n\t****MY SHELL****";
    cout << "\n\n\t-USE AT YOUR OWN RISK-";
    cout << "\n\n******************************************";
    char *username = getenv("USER");
    cout << "\n\n\nUSER is: @%s" << username;
    cout << "\n";
    sleep(3);
    // clear();
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
        close(pipefd[0]); // cierra lectura hijo
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // cierra escritura de hijo

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
    cout << "\n\n---SYSTEMA DE AYUDA---"
         << "\nCOMANDOS SOPORTADOS:"
         << "\n>cd"
         << "\n>ls"
         << "\n>exit"
         << "\n>TODOS LOS COMANDOS DISPONIBLES EN UNIX SHELL"
         << "\n>MANIPULACION DE TUBERIAS";

    return;
}

int ownCmdHandler(char **parsed) // controlador de comandos propios
{
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char *ListOfOwnCmds[NoOfOwnCmds];
    char *username;

    string mystring = "exit";
    std::vector<char> v(mystring.length() + 1);
    std::strcpy(&v[0], mystring.c_str());
    char *str1 = &v[0];

    string mystring2 = "cd";
    std::vector<char> v2(mystring2.length() + 1);
    std::strcpy(&v2[0], mystring2.c_str());
    char *str2 = &v2[0];

    string mystring3 = "help";
    std::vector<char> v3(mystring3.length() + 1);
    std::strcpy(&v3[0], mystring3.c_str());
    char *str3 = &v3[0];

    string mystring4 = "hello";
    std::vector<char> v4(mystring4.length() + 1);
    std::strcpy(&v4[0], mystring4.c_str());
    char *str4 = &v4[0];

    ListOfOwnCmds[0] = str1;
    ListOfOwnCmds[1] = str2;
    ListOfOwnCmds[2] = str3;
    ListOfOwnCmds[3] = str4;

    for (i = 0; i < NoOfOwnCmds; i++)
    {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0)
        {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg)
    {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
               "not a place to play around."
               "\nUse help to know more..\n",
               username);
        return 1;
    default:
        break;
    }

    return 0;
}

int parsePipe(char *str, char **strpiped) // retorna si encuentra tuberia
{
    int i;
    for (i = 0; i < 2; i++)
    {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else
    {
        return 1;
    }
}

void parseSpace(char *str, char **parsed) // separa el comando en argumentos segun espacios
{
    int i;

    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int processString(char *str, char **parsed, char **parsedpipe)
{

    char *strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped)
    {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
    }
    else
    {

        parseSpace(str, parsed);
    }

    if (ownCmdHandler(parsed)) //
        return 0;              // hay comandos propios dentro de los argumentos
    else
        return 1 + piped;
    // 1 no hay comados propios
    // 2 no hay comados propios pero hay tuberia
}

int main()
{
    // cout << "Hello World!\n";
    // inicio();
    // system("pause");
    // return 0;

    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char *parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    inicio();

    while (1)
    {
        // print shell line
        printDir();
        // take input
        if (takeInput(inputString))
            continue;
        // process
        execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
        // execflag returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
        // 2 if it is including a pipe.

        // execute
        if (execFlag == 1)
            execArgs(parsedArgs);

        if (execFlag == 2)
            execArgsPiped(parsedArgs, parsedArgsPiped);
    }
    return 0;
}
