

#include <sstream>
#include <mutex>
#include "ed3_lib.h"
#include "functions.h"
#include "Token.h"
#include "process.h"

using namespace std;

static mutex mtx;

Token::Token()
{
    pid = 0;
    state = TOKEN_FREE;
    root = NULL;
}

Token::~Token()
{
    pid = 0;
    root->getLeft()->setRight(NULL);
    root->setLeft(NULL);
    while (root->getRight() != NULL)
    {
        root = root->getRight();
        root->setLeft(NULL);
    }
    root = NULL;
}

void Token::setPid(uint32 pid) { this->pid = pid; }
uint32 Token::getPid() const { return this->pid; }
void Token::setState(uint32 new_state) { this->state = new_state; }
uint32 Token::getState() const { return this->state; }
void Token::addProcess(Process *hprocess)
{
//Caso não tennha nenhum nó na raiz, adicione, e já definao acesso
    if (root == NULL)
    {
        root = hprocess;
        setPid(hprocess->getId());
        setState(TOKEN_USE);
    }
    else if (root->getRight() == NULL)
    {
        root->setLeft(hprocess);
        root->setRight(hprocess);
        hprocess->setLeft(root);
        hprocess->setRight(root);
    }
    else
    {
        hprocess->setLeft(root->getLeft());
        hprocess->getLeft()->setRight(hprocess);
        root->setLeft(hprocess);
        hprocess->setRight(root);
    }
}
void Token::print()
{
    stringstream ss;
    ss << "Imprimindo processos..." << endl;
    int x = 0;
    Process *hprocess = root;
    while (x <= 3)
    {
        if (hprocess->getId() == root->getId())
        {
            x++;
if(x>3) continue;
            ss << endl
               << "Ciclo " << x << " de 3" << endl;
        }
        ss << hprocess->getId() << "\t";
        hprocess = hprocess->getRight();
    }
    _FLOG("{}", ss.str());
}
bool Token::transferAccess(Process *hprocess)
{
    if (hprocess->getId() != this->getPid())
    {
        return false;
    }
    setState(TOKEN_TRANSFER);
    setPid(hprocess->getRight()->getId());
    setState(TOKEN_USE);
    return true;
}
void Token::getAccess(Process *handle)
{
    // lock_guard<mutex> lck(mtx);
    if (handle->getId() == getPid())
    {
        return;
    }
    if (getState() == TOKEN_FREE)
    {
        setState(TOKEN_USE);
        setPid(handle->getId());
        return;
    }
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if ((this->getPid() == handle->getId()) && (this->getState() == TOKEN_USE))
        {
            break;
        }
    }
}
