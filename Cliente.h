#ifndef CLIENTE_H
#define CLIENTE_H
#include "Carro.h"
#include "Pessoa.h"
#include <string>
using namespace std;

// classe para um cliente, que herda de pessoa
class Cliente : public Pessoa
{
private:
    Carro carro;

public:
    // construtor
    Cliente(const string &nome, const string &modelo, const string &placa, float kilometragem);

    // getter
    Carro &getCarro();
};

#endif 