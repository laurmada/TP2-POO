#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <string>
#include <vector>
#include "Pessoa.h"  

using namespace std;

// classe para representar um funcionario, que herda de pessoa
class Funcionario : public Pessoa {
protected:
    string senha;

public:
    // construtor
    Funcionario(const string &nome, const string &senha);

    // metodos
    void setSenha(const string &novaSenha);
    bool verificarSenha(const string &senha) const;
    virtual void menu() = 0;
};

#endif