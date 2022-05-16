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
    sleep(1);
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
         << "\n>MANIPULACION DE TUBERIAS"
         << "\n>";
    return;
}

void mostrarDireccionActual()
{
    char dirActual[1024];
    getcwd(dirActual, sizeof(dirActual)); // captura direccion
    cout << "\nDir:[~" << dirActual << "]";
}

char* indiceHistorial(char *comando){

        if (strcmp(comando, "!1") == 0)
        {
           cout<<strcat(comando,"1");
            

        }

        if(comando == "!1" ||  comando == "!2" || comando == "!3" ||
        comando == "!4" || comando == "!5"){

        HISTORY_STATE *historial = history_get_history_state ();
        HIST_ENTRY **listHis = history_list ();

        cout<<"comando";
        comando = listHis[historial->length-1]->line;
        
        }

    return comando;
}

int isComandoNULL(char *str) // si el comando no es nulo lo agrega al historial
{

    char *comando;
    char *username = getenv("USER");
    cout << endl
         << endl
         << "[" << username << "]";
    comando = readline("->>");
    if (strlen(comando) == 0) // si esta vacio
    {
        return 1;
    }
    else
    {
        // si se encuentra !# se cambia comando a comando en historial
        comando = indiceHistorial(comando);

        add_history(comando);
        strcpy(str, comando);
        return 0;
    }
}

int encontrarPipe(char *comando, char **tuberia)
{
    // encuentrar tuberia
    for (int i = 0; i < 2; i++)
    { // strsep extrae elemento de cadena
        tuberia[i] = strsep(&comando, "|");
        if (tuberia[i] == NULL)
            break;
    }

    if (tuberia[1] == NULL)
    {
        return 0; // si se encuentra tuberia.
    }
    else
    {
        return 1; // si no encuentra tuberia
    }
}

void separarComando(char *comando, char **argumentos)
{
    // separacion de comando en argumentos separados
    for (int i = 0; i < MAXLIST; i++)
    {
        argumentos[i] = strsep(&comando, " "); // separacion por espacios

        if (argumentos[i] == NULL)
        { // termina separacion
            break;
        }
        if (strlen(argumentos[i]) == 0)
        { // evitar llenar argumentos vacios
            i--;
        }
    }
}

void mostarHistorial(){
    char *usuario = getenv("USER");

    /* obtener estado de lista de historial (offset, length, size) */
    HISTORY_STATE *historial = history_get_history_state ();
    /* recuperar lista de historial */
    HIST_ENTRY **listHis = history_list ();
    cout<<"\nhistorial de usuario: "<< usuario <<endl;

    int contador = 10;
    if(historial->length > 10){
    
    for(int j= 0; j < historial->length-10;j++){
            free_history_entry (listHis[j]);    
    }

    for (int i = historial->length-10; i < historial->length; i++) { /* mostrar historial*/
        cout<<contador<<"  ";
        printf (" %8s  %s\n", listHis[i]->line, listHis[i]->timestamp);
        contador--;
    }
    putchar ('\n');


    }else{
        contador = historial->length;

    for (int i = 0; i < historial->length; i++) { /* mostrar historial*/
        cout<<contador<<"  ";
        printf (" %8s  %s\n", listHis[i]->line, listHis[i]->timestamp);
        contador--;   
    }
    putchar ('\n');

    }

}

int comandosPropios(char **argumentos)
{
    // controlador de comandos propios

    int numCom = 4;
    int selector = 0;
    char *comPropios[numCom];

    string mystring = "exit";
    vector<char> v(mystring.length() + 1);
    strcpy(&v[0], mystring.c_str());
    char *str1 = &v[0];

    string mystring2 = "cd";
    vector<char> v2(mystring2.length() + 1);
    strcpy(&v2[0], mystring2.c_str());
    char *str2 = &v2[0];

    string mystring3 = "help";
    vector<char> v3(mystring3.length() + 1);
    strcpy(&v3[0], mystring3.c_str());
    char *str3 = &v3[0];

    string mystring4 = "historial";
    vector<char> v4(mystring4.length() + 1);
    strcpy(&v4[0], mystring4.c_str());
    char *str4 = &v4[0];

    comPropios[0] = str1;
    comPropios[1] = str2;
    comPropios[2] = str3;
    comPropios[3] = str4;


    for (int i = 0; i < numCom; i++)
    { // comparacion
        if (strcmp(argumentos[0], comPropios[i]) == 0)
        {
            selector = i + 1;
            break;
        }
    }

    switch (selector)
    {
    case 1:
    {
        cout << "\nFIN...\n"
             << endl;
        exit(0);
    }

    case 2:
    {
        chdir(argumentos[1]);
        return 1;
    }

    case 3:
    {
        ayuda();
        return 1;
    }
    case 4:
    {
        mostarHistorial();
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

    if (comandosPropios(argumentos))
    { // buscar un comando propio dentro de argumentos de comando
        return 0;
    }
    else
    {
        return 1 + piped;
    }
}

void ejecutarArgsSimples(char **argAnalizado)
{
    // Bifurcacion del hijo
    pid_t pid = fork();

    if (pid == -1)
    {
        cout << "\n La creación del hijo ha fallado";
        return;
    }
    else if (pid == 0)
    {
        if (execvp(argAnalizado[0], argAnalizado) < 0)
        {
            cout << "\n No se puede ejecutar la sentencia";
        }
        exit(0);
    }
    else
    {
        // El padre espera a que el hjo termine la instrucción
        wait(NULL);
        return;
    }
}

void ejecutarArgsPipe(char **argAnalizado, char **argPipe)
{
    // 0 es lectura, 1 escritura en tuberia
    int tuberiaRW[2];
    pid_t pid1, pid2;

    if (pipe(tuberiaRW) < 0)
    {
        printf("\nNo se pudo inicializar la tuberia");
        return;
    }

    // Creación del hijo 1
    pid1 = fork();

    if (pid1 < 0)
    {
        printf("\n No se puede crear el hijo 1");
        return;
    }

    // hijo 1
    if (pid1 == 0)
    {
        close(tuberiaRW[0]); // cierra lectura hijo
        dup2(tuberiaRW[1], STDOUT_FILENO);
        close(tuberiaRW[1]); // cierra escritura de hijo

        if (execvp(argAnalizado[0], argAnalizado) < 0)
        {
            printf("\nNo se puede ejecuatr el comando 1");
            exit(0);
        }
    }
    else
    {
        // Creación del hijo 2
        pid2 = fork();

        if (pid2 < 0)
        {
            printf("\nNo se pudo crear el hijo 2");
            return;
        }

        // Se ejecuta el hijo 2
        if (pid2 == 0)
        {
            close(tuberiaRW[1]); // cierra escritura hijo 2
            dup2(tuberiaRW[0], STDIN_FILENO);
            close(tuberiaRW[0]); // cierra lectura de hijo 2
            if (execvp(argPipe[0], argPipe) < 0)
            {
                printf("\nNo se puede ejecutar el comando 2");
                exit(0);
            }
        }
        else
        {
            // El padre espera a que terminen de ejecuatarse los hijos
            wait(NULL);
            wait(NULL);
        }
    }
}

void ejecutarComando(int bandera, char **args, char **argsPipe)
{
     if (bandera == 1)
         ejecutarArgsSimples(args);

     if (bandera == 2)
         ejecutarArgsPipe(args, argsPipe);
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