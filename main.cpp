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
//#define MAXCOM 1000
#define MAX_LINE 80
//#define clear() cout << "\033[H\033[j";

using namespace std;



void inicio()
{
    system("clear");
    cout << "\n\n------------------------------------------";
    cout << "\n\n\t- UNIVERSIDAD NACIONAL -";
    cout << "\n\n\t- Sistemas Opertivos -";
    cout << "\n\n\t- Proyecto CLI Linux -";
    cout << "\n\n\t- Keiner Godinez - Ronald Blanco -";
    cout << "\n\n-------------------------------------------";
    char *username = getenv("USER");
    cout << "\n\n\nUSER is: @%s" << username;
    cout << "\n";
    sleep(3);
}

void mostrarDireccionActual()
{
    char dirActual[1024];
    getcwd(dirActual, sizeof(dirActual));// captura direccion
    cout<<"\nDir: %s"<<dirActual;
}

int isComandoNULL()//char *str // si el comando no es nulo lo agrega al historial
{
    char *comando;
    comando = readline("\n>>> ");
    if (strlen(comando) == 0)// si esta vacio
    {
        return 1;
    }
    else
    {
        // add_history(buf);
        // strcpy(str, buf);
        return 0;
    }
    
}

int procesarComando(char *str, char **parsed, char **parsedpipe)
{

    // char *strpiped[2];
    // int piped = 0;

    // piped = parsePipe(str, strpiped);

    // if (piped)
    // {
    //     parseSpace(strpiped[0], parsed);
    //     parseSpace(strpiped[1], parsedpipe);
    // }
    // else
    // {

    //     parseSpace(str, parsed);
    // }

    // if (ownCmdHandler(parsed)) //
        return 0;
    // else
    //     return 1 + piped;
}

void ejecutarComando(int bandera){
    // execflag returns zero if there is no command
    // or it is a builtin command,
    // 1 if it is a simple command
    // 2 if it is including a pipe.
    
    // execute
    // if (bandera == 1)
    //     execArgs(parsedArgs);

    // if (bandera == 2)
    //     execArgsPiped(parsedArgs, parsedArgsPiped);
}

int main(){


    char comandoEntrada[MAX_LINE]; // almacenar comando
    int bandera = 0;// bandera ejecucion
    char *argumentos[MAX_LINE];// argumentos analisados comando
    char *argumentosPipe[MAX_LINE];// argumentos analisados comando con Pipe

    inicio();

        while (1)
    {

        mostrarDireccionActual();

        if (!isComandoNULL()){// si el comando NO esta vacio
            
            // bandera = procesarComando(comandoEntrada, argumentos);
            // ejecutarComando(bandera);

        }
    }


    return 0;
}