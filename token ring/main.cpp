
/**
*Implementação básica do algoritmo de exclusão mútua token ring
*Trabalho de SD2 de 11/04/2022
*Escrito por Róger Matheus Lasch
*Compilado e testado com Visual Studio Community 2022
*Comando de compilação:
*cl /nologo /EHsc /std:c++latest *.cpp
**/

#include <iostream>
#include<functional>
#include <string>
#include <format>
#include "ed3_lib.h"
#include "functions.h"
#include "Token.h"
#include "process.h"

using namespace std;

void createThreads(vector<Process *> process, vector<thread> &threads);
void waitThreads(vector<thread> &threads);
int main()
{
    setlocale(LC_ALL, "Portuguese");
    Token tk;
    vector<Process *> process;
    vector<thread> threads;
//Inicializa os processos...
    for (int i = 1; i < 5; i++)
    {
        Process *sf = new Process();
        sf->setToken(&tk);
        sf->setId(i);
        tk.addProcess(sf);
        process.push_back(sf);
    }
    tk.print();
    system("pause");
//Executa a simulação durante duas voltas...
    for (int i = 0; i < 2; i++)
    {
        createThreads(process, threads);
        waitThreads(threads);
    }
//Limpa os processos...
    for (auto &it : process)
    {
        delete it;
    }
    return 0;
}

void createThreads(vector<Process *> process, vector<thread> &threads)
{
    for (uint32 i = 0; i < process.size(); i++)
    {
//Encapsula o método da classe a ser executado assincronamente...
        function<void()> my_function = std::bind(&Process::run_function, process[i]);
//cria um thread com a função a ser executada..
        threads.emplace_back(my_function);
    }
}

void waitThreads(vector<thread> &threads)
{
//Espera todos os threads terminarem a execução...
    for (auto &it : threads)
    {
        it.join();
    }
    threads.clear();
}
