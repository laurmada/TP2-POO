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
    // destrutor e construtor
    Pessoa();
    Pessoa(const string nome);

    // getter
    string getNome() const;

    // setter
    void setNome(const string nome);
};

#endif 