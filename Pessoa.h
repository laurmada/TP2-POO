#ifndef PESSOA_H
#define PESSOA_H

#include <string>
using namespace std;

// classe que representa uma pessoa
class Pessoa
{
protected:
    string nome;

public:
    Pessoa();
    Pessoa(const string nome);
    string getNome() const;
    void setNome(const string nome);
};

#endif 