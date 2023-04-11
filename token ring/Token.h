

#ifndef TOKEN_H
#define TOKEN_H

enum TOKEN_STATES
{
    TOKEN_FREE = 0,
    TOKEN_USE,
    TOKEN_TRANSFER
};

class Process;
class Token
{
private:
    uint32 pid;//Id do processo que está no acesso crítico...
    uint32 state;//Estado do token
    Process *root;//Processo raiz

public:
    Token();
    ~Token();
    void setPid(uint32 pid);
    uint32 getPid() const;
    void setState(uint32 new_state);
    uint32 getState() const;
    void addProcess(Process *hprocess);
    void print();
    bool transferAccess(Process *hprocess);
    void getAccess(Process *handle);
};
#endif
