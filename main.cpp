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

int isComandoNULL(char *str) // si el comando no es nulo lo agrega al historial
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
        strcpy(str, comando);
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

    // if (ownCmdHandler(parsed)) //buscar un comando propio dentro de argumentos de comando
        return 0;
    // else
    //     return 1 + piped;
}

void ejecutarComando(int bandera, char **args, char **argsPipe){
    // if (bandera == 1)
    //     ejecutarArgsSimples(args);

    // if (bandera == 2)
    //     ejecutarArgsPipe(args, argsPipe);
}

int main(){

    char comandoEntrada[MAXCOM]; // almacenar comando
    int bandera = 0;// bandera ejecucion
    char *argumentos[MAXLIST];// argumentos analisados comando
    char *argumentosPipe[MAXLIST];// argumentos analisados comando con Pipe

    inicio();

        while (1)
    {
        mostrarDireccionActual();

        if (!isComandoNULL(comandoEntrada)){// si el comando NO esta vacio
            
            bandera = procesarComando(comandoEntrada, argumentos, argumentosPipe);
            ejecutarComando(bandera,argumentos, argumentosPipe);
        }
    }

    return 0;
}

    // char* c= "d,s,v,f";
    // char c[] = "d,s,v,f",;

    // char *c[] = "d,s,v,f", "d,s,v,f", "d,s,v,f"

    // =
    // "d,s,v,f", 
    // "d,s,v,f",
    // "d,s,v,f"