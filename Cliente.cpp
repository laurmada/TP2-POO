#include "Cliente.h"
#include "Carro.h"

Cliente::Cliente(const string &nome, const string &modelo, const string &placa, float kilometragem)
    : Pessoa(nome), carro(modelo, placa, kilometragem) {}
Carro &Cliente::getCarro() { return carro; }