#include "Cliente.h"
#include "Carro.h"

// construtor
Cliente::Cliente(const string &nome, const string &modelo, const string &placa, float kilometragem)
    : Pessoa(nome), carro(modelo, placa, kilometragem) {}

// getter
Carro &Cliente::getCarro() { return carro; }