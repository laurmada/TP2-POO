#include "Pessoa.h"

Pessoa::Pessoa() {}

Pessoa::Pessoa(const string nome) : nome(nome) {}

string Pessoa::getNome() const
{
    return nome;
}
void Pessoa::setNome(const string nome)
{
    this->nome = nome;
}