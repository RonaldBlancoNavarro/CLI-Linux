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
    cout << "\n\n\nUSER is:" << username;
    cout << "\n";
    sleep(3);
}

void ayuda()
{
    cout << "\n\n---SYSTEMA DE AYUDA---"
         << "\nCOMANDOS SOPORTADOS:"
         << "\n>cd"
         << "\n>ls"
         << "\n>rm"
         << "\n>cp"
         << "\n>exit"
         << "\n>TODOS LOS COMANDOS DISPONIBLES EN UNIX SHELL"
         << "\n>MANIPULACION DE TUBERIAS";
    return;
}

void mostrarDireccionActual()
{
    char dirActual[1024];
    getcwd(dirActual, sizeof(dirActual)); // captura direccion
    cout << "\nDir:[~" << dirActual<< "]";
}

int isComandoNULL(char *str) // si el comando no es nulo lo agrega al historial
{
    
    char *comando;
    char *username = getenv("USER");
    cout <<endl<<endl<<"[" <<username <<"]";
    comando = readline("->>");
    if (strlen(comando) == 0) // si esta vacio
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

int encontrarPipe(char *comando, char **tuberia)
{
// encuentrar tuberia
    for (int i = 0; i < 2; i++)
    {   // strsep extrae elemento de cadena
        tuberia[i] = strsep(&comando, "|");
        if (tuberia[i] == NULL)
            break;
    }

    if (tuberia[1] == NULL){
        return 0; // si se encuentra tuberia.
    }
    else{
        return 1;// si no encuentra tuberia
    }
}

void separarComando(char *comando, char **argumentos){
    // separacion de comando en argumentos separados
    for (int i = 0; i < MAXLIST; i++)
    {
        argumentos[i] = strsep(&comando, " ");// separacion por espacios

        if (argumentos[i] == NULL){// termina separacion
            break;
        }
        if (strlen(argumentos[i]) == 0){// evitar llenar argumentos vacios
            i--;
        }
    }
}

int comandosPropios(char **argumentos) 
{
    //controlador de comandos propios

    int numCom = 3;
    int selector = 0;
    char *comPropios[numCom];

    string mystring = "exit";
    vector<char> v(mystring.length() + 1);
    strcpy(&v[0], mystring.c_str());
    char* str1=  &v[0];

    string mystring2 = "cd";
    vector<char> v2(mystring2.length() + 1);
    strcpy(&v2[0], mystring2.c_str());
    char* str2=  &v2[0];

    string mystring3 = "help";
    vector<char> v3(mystring3.length() + 1);
    strcpy(&v3[0], mystring3.c_str());
    char* str3 =  &v3[0];

    comPropios[0] = str1;
    comPropios[1] = str2;
    comPropios[2] = str3;


    for (int i = 0; i < numCom; i++)
    {   // comparacion
        if (strcmp(argumentos[0], comPropios[i]) == 0)
        {
            selector = i + 1;
            break;
        }
    }

    switch (selector)
    {
    case 1:{
        cout<<"\nFIN...\n"<<endl;
        exit(0);
    }

    case 2:{
        chdir(argumentos[1]);
        return 1;
    }

    case 3:{
        ayuda();
        return 1;
    }

    default:
        break;
    }

    return 0;
}

int procesarComando(char *comando, char **argumentos, char **argumentosPipe)
{
    char *tuberia[2];
    int piped = 0;

    piped = encontrarPipe(comando, tuberia);

    if (piped)
    {
        separarComando(tuberia[0], argumentos);
        separarComando(tuberia[1], argumentosPipe);
    }
    else
    {
        separarComando(comando, argumentos);
    }

    if (comandosPropios(argumentos)){ //buscar un comando propio dentro de argumentos de comando
        return 0;
    }
    else{
        return 1 + piped;
    }
}

void ejecutarComando(int bandera, char **args, char **argsPipe)
{
    // if (bandera == 1)
    //     ejecutarArgsSimples(args);

    // if (bandera == 2)
    //     ejecutarArgsPipe(args, argsPipe);
}

int main()
{

    char comandoEntrada[MAXCOM];   // almacenar comando
    int bandera = 0;               // bandera ejecucion
    char *argumentos[MAXLIST];     // argumentos analisados comando
    char *argumentosPipe[MAXLIST]; // argumentos analisados comando con Pipe

    inicio();

    while (true)
    {
        mostrarDireccionActual();

        if (!isComandoNULL(comandoEntrada))
        { // si el comando NO esta vacio

            bandera = procesarComando(comandoEntrada, argumentos, argumentosPipe);
            ejecutarComando(bandera, argumentos, argumentosPipe);
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