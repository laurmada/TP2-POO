#include "Pessoa.h"

// destrutor e construtor
Pessoa::Pessoa() {}
Pessoa::Pessoa(const string nome) : nome(nome) {}

// getter
string Pessoa::getNome() const
{
    return nome;
}

// setter
void Pessoa::setNome(const string nome)
{
    this->nome = nome;
}