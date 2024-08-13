#include "Carro.h"
// construtor
Carro::Carro(const string &modelo, const string &placa, float kilometragem) : modelo(modelo), placa(placa), kilometragem(kilometragem) {}

// getters
string Carro::getModelo() const { return modelo; }
string Carro::getPlaca() const { return placa; }
float Carro::getKilometragem() const { return kilometragem; }

//setters
void Carro::setModelo(string &modelo) { this->modelo = modelo; }
void Carro::setPlaca(string &placa) { this->placa = placa; }
void Carro::setKilometragem(float kilometragem) { this->kilometragem = kilometragem; }