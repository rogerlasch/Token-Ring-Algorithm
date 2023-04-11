

#ifndef PROCESS_H
#define PROCESS_H

class Token;
class Process
{
    uint32 id;//Id do processo
    Token *token;//Objeto de token
    Process *left;//Vizinho da esquerda
    Process *right;//Vizinho da direita

public:
    Process();
    Process(const Process &pr) = delete;
    Process &operator=(const Process &pr) = delete;
    virtual ~Process();
    void setId(uint32 id);
    uint32 getId() const;
    void setLeft(Process *pleft);
    Process *getLeft() const;
    void setRight(Process *pleft);
    Process *getRight() const;
    void setToken(Token *tk);
    Token *getToken() const;
    bool hasToken() const;
    void run_function();
    ;
};
#endif
