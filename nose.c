// C Program to design a shell in Linux
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(){

    char *ListOfOwnCmds[4];

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";

    //for (size_t i = 0; i < 4; i++)
    //{
        int n = 2;
        printf(n);
        /* code */
    //}n
    


    return 0;
}