#include <iostream>

using namespace std;

void saalir(string texto)
{

    if (texto == "ex")
    {
        system("exit");
    }
    if (texto == "ls")
    {
        system("DIR");
    }
}

void cmd()
{

    while (true)
    {

        cout << "Comandos:";
        string comando;
        getline(cin, comando);
        if (comando == "ex")
        {
            break;
        }
        if (comando == "ls")
        {
            system("g++ --version");
        }
        // system(comando.c_str());
        // if(comando == "exit" || comando == "EXIT")break;
    }
}

int main()
{

    cmd();
    system("pause");
    return 0;
}

/*
#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
int main()
{
    // create a variable to hold the process ID
    pid_t pid;

    // create a child process
    // thus making 2 processes run at the same time
    // Store the Process ID in 'pid'
    pid = fork();

    // Check if 'pid' is 0
    // If yes, then it's parent process
    // Else, it is the child process
    if (pid == 0)
        cout << "Output from the child process." << endl;
    else
        cout << "Output from the parent process." << endl;

    return 0;
}*/
