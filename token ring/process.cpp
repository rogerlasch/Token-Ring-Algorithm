

#include <thread>
#include <chrono>
#include "ed3_lib.h"
#include "functions.h"
#include "Token.h"
#include "process.h"

using namespace std;

Process::Process()
{
    this->id = 0;
    token = NULL;
    left = NULL;
    right = NULL;
}

Process::~Process()
{
}

void Process::setId(uint32 id) { this->id = id; }

uint32 Process::getId() const { return this->id; }

void Process::setLeft(Process *pleft) { this->left = pleft; }
Process *Process::getLeft() const { return this->left; }
void Process::setRight(Process *pright) { this->right = pright; }
Process *Process::getRight() const { return this->right; }
void Process::setToken(Token *tk) { this->token = tk; }
Token *Process::getToken() const { return this->token; }
bool Process::hasToken() const { return token != NULL && this->getId() == token->getPid(); }

void Process::run_function()
{
//Espera até conseguir o acesso...
    token->getAccess(this);
    _FLOG("{} adquiriu o token.", getId());
    //Faça algo...
    this_thread::sleep_for(chrono::milliseconds(3000));
    _FLOG("{} está deixando a região crítica...", getId());
//Transfere o acesso para outro...
    token->transferAccess(this);
}
